#include "curl.hpp"
#include "garbage_cleaner.hpp"
#include <chucho/log.hpp>

namespace
{

std::once_flag global_once;

void global_setup()
{
    curl_global_init(CURL_GLOBAL_ALL);
    espadin::garbage_cleaner::get().add([] () { curl_global_cleanup(); });
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
      verbose_(false)
{
    std::call_once(global_once, global_setup);
    curl_ = curl_easy_init();
    if (curl_ == nullptr)
        throw std::runtime_error("Could not initialize libcurl");
    set_option(CURLOPT_WRITEFUNCTION, written_callback, "write funtion");
}

curl::~curl()
{
    if (curl_ != nullptr)
        curl_easy_cleanup(curl_);
}

curl_slist* curl::create_slist(std::vector<std::string>&& items)
{
    curl_slist* result = nullptr;
    if (!items.empty())
    {
        auto sl = curl_slist_append(nullptr, items.front().c_str());
        items.erase(items.begin());
        for (const auto& s : items)
            sl = curl_slist_append(sl, s.c_str());
        slists_.emplace_back(decltype(slists_)::value_type(sl, curl_slist_free_all));
        result = sl;
    }
    return result;
}

std::string curl::escape(const std::string& str) const
{
    std::string result;
    auto loc = curl_easy_escape(curl_, str.c_str(), str.length());
    result = loc;
    curl_free(loc);
    return result;
}

bool curl::get_ssl_supported()
{
    std::call_once(global_once, global_setup);
    curl_version_info_data *ver = curl_version_info(CURLVERSION_NOW);
    return (ver->features & CURL_VERSION_SSL) != 0;
}

std::unique_ptr<cjson::doc> curl::perform()
{
    std::string written;
    set_option(CURLOPT_WRITEDATA, &written, "write data");
    auto rc = curl_easy_perform(curl_);
    if (rc != CURLE_OK)
        throw curl_exception(rc, "Could not perform CURL operation");
    CHUCHO_TRACE_L("Received reply: " << written);
    return std::move(std::make_unique<cjson::doc>(written));
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

curl::curl_exception::curl_exception(CURLcode err, const std::string& msg)
    : std::runtime_error(msg + ": " + curl_easy_strerror(err))
{
}

}
