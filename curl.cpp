#include "curl.hpp"
#include "garbage_cleaner.hpp"
#include <espadin/exception.hpp>
#include <chucho/log.hpp>
#include <cassert>

namespace
{

std::once_flag global_once;

void global_setup()
{
    curl_global_init(CURL_GLOBAL_ALL);
    espadin::garbage_cleaner::get().add([] () { curl_global_cleanup(); });
}

std::string to_lower(const std::string& str)
{
    std::string result;
    std::transform(str.begin(),
                   str.end(),
                   std::back_inserter(result),
                   [] (unsigned char c) -> unsigned char { return std::tolower(c); });
    return result;
}

std::string trim(const std::string& str)
{
    std::string result(str);
    result.erase(0, result.find_first_not_of(" \t\r\n"));
    if (!result.empty())
    {
        auto last = result.find_last_not_of(" \t\r\n");
        if (last < result.length() - 1)
            result.erase(last + 1);
    }
    return result;
}

std::size_t header_callback(char* buf, std::size_t sz, std::size_t num, void* udata)
{
    assert(sz == 1);
    auto headers = reinterpret_cast<std::map<std::string, std::string>*>(udata);
    std::string line(buf, num);
    auto colon = line.find(':');
    if (colon < line.length() - 1)
    {
        auto key = to_lower(trim(line.substr(0, colon)));
        auto value = trim(line.substr(colon + 1));
        if (!key.empty())
            headers->insert(std::make_pair(key, value));
    }
    return num;
}

std::size_t written_callback(char* data, std::size_t sz, std::size_t num, void* user)
{
    auto str = reinterpret_cast<std::string*>(user);
    auto total = sz * num;
    str->append(data, total);
    return total;
}

}

namespace espadin
{

int curl_debug_callback(CURL* crl,
                        curl_infotype info_type,
                        char* text,
                        std::size_t num,
                        void* user_data)
{
    CHUCHO_DEBUG(static_cast<curl*>(user_data)->get_logger(), std::string(text, num));
    return 0;
}

curl::curl()
    : curl_(nullptr),
      verbose_(false),
      response_code_(0)
{
    std::call_once(global_once, global_setup);
    curl_ = curl_easy_init();
    if (curl_ == nullptr)
        throw std::runtime_error("Could not initialize libcurl");
    // HTTP/2 framing won't succeed when sending multipart post data
    set_option(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1, "HTTP version");
    set_option(CURLOPT_WRITEFUNCTION, written_callback, "write funtion");
    set_option(CURLOPT_HEADERFUNCTION, header_callback, "header callback");
    set_option(CURLOPT_HEADERDATA, &response_headers_, "header data");
}

curl::~curl()
{
    if (curl_ != nullptr)
        curl_easy_cleanup(curl_);
}

std::string curl::escape(const std::string& str) const
{
    std::string result;
    auto loc = curl_easy_escape(curl_, str.c_str(), str.length());
    result = loc;
    curl_free(loc);
    return result;
}

std::optional<std::string> curl::header(const std::string& key)
{
    std::optional<std::string> result;
    auto found = headers_.find(key);
    if (found != headers_.end())
        result = found->second;
    return result;
}

void curl::maybe_set_post_parts(std::vector<char>& result)
{
    if (!post_parts_.empty())
    {
        std::ostringstream stream;
        stream << "Espadin-Part-" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto boundary = stream.str();
        std::string content_type;
        auto itor = headers_.find("Content-Type");
        if (itor != headers_.end())
            content_type = itor->second;
        else
            content_type = "multipart/related";
        headers_["Content-Type"] = content_type + "; boundary=" + boundary;
        for (const auto& tup : post_parts_)
        {
            result.push_back('-');
            result.push_back('-');
            result.insert(result.end(), boundary.begin(), boundary.end());
            std::string piece("\r\nContent-Type: " + std::get<0>(tup) + "\r\n\r\n");
            result.insert(result.end(), piece.begin(), piece.end());
            std::visit([&result](const auto& val) { for (auto c : val) { result.push_back(static_cast<char>(c)); } }, std::get<1>(tup));
            result.push_back('\r');
            result.push_back('\n');
        }
        result.push_back('-');
        result.push_back('-');
        result.insert(result.end(), boundary.begin(), boundary.end());
        result.push_back('-');
        result.push_back('-');
        result.push_back(0);
        headers_["Content-Length"] = std::to_string(result.size() - 1);
        set_option(CURLOPT_POSTFIELDS, &result[0], "POST fields");
        set_option(CURLOPT_POSTFIELDSIZE_LARGE, result.size(), "POST fields size");
    }
}

std::unique_ptr<cjson::doc> curl::perform()
{
    std::vector<char> postable;
    maybe_set_post_parts(postable);
    curl_slist* hlist = nullptr;
    for (const auto& p : headers_)
    {
        std::string h = p.first + ": " + p.second;
        hlist = curl_slist_append(hlist == nullptr ? nullptr : hlist, h.c_str());
    }
    set_option(CURLOPT_HTTPHEADER, hlist, "HTTP header");
    std::string written;
    set_option(CURLOPT_WRITEDATA, &written, "write data");
    response_headers_.clear();
    response_code_ = 0;
    auto rc = curl_easy_perform(curl_);
    if (rc != CURLE_OK)
        throw curl_exception(rc, "Could not perform CURL operation");
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &response_code_);
    CHUCHO_TRACE_L("Received reply (" << response_code_ << "): " << written);
    curl_slist_free_all(hlist);
    std::unique_ptr<cjson::doc> result;
    try
    {
        if (!written.empty())
        {
            result = std::make_unique<cjson::doc>(written);
            if (cJSON_HasObjectItem(**result, "error"))
                throw drive_exception(***result);
        }
    }
    catch (const drive_exception& de)
    {
        throw;
    }
    catch (const std::exception& e)
    {
        CHUCHO_DEBUG_L("JSON error: " << e.what());
    }
    return std::move(result);
}

std::optional<std::string> curl::response_header(const std::string& key)
{
    auto found = response_headers_.find(to_lower(key));
    std::optional<std::string> result;
    if (found != response_headers_.end())
        result = found->second;
    return result;
}

void curl::set_verbose(bool state)
{
    if (state && !verbose_)
    {
        set_option(CURLOPT_DEBUGFUNCTION, curl_debug_callback, "debug callback");
        set_option(CURLOPT_DEBUGDATA, this, "debug user data pointer");
        set_option(CURLOPT_VERBOSE, 1, "verbose output");
    }
    else if (!state && verbose_)
    {
        set_option(CURLOPT_DEBUGFUNCTION, nullptr, "debug callback");
        set_option(CURLOPT_DEBUGDATA, nullptr, "debug user data pointer");
        set_option(CURLOPT_VERBOSE, 0, "verbose output");
    }
    verbose_ = state;
}

bool curl::ssl_supported()
{
    std::call_once(global_once, global_setup);
    curl_version_info_data* ver = curl_version_info(CURLVERSION_NOW);
    return (ver->features & CURL_VERSION_SSL) != 0;
}

curl::curl_exception::curl_exception(CURLcode err, const std::string& msg)
    : std::runtime_error(msg + ": " + curl_easy_strerror(err))
{
}

}
