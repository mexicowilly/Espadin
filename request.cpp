#include "request.hpp"
#include "resumable_file_upload.hpp"
#include <espadin/exception.hpp>
#include <chucho/log.hpp>
#include <sstream>
#include <cassert>
#include <fstream>
#include <cstring>

namespace
{

const std::string BASE_URL("https://www.googleapis.com/{}drive/v3/");

}

namespace espadin
{

request::request(const std::string& access_token)
{
    curl_.header("Authorization", "Bearer " + access_token);
}

bool request::is_upload() const
{
    return false;
}

std::string request::parameters_as_url() const
{
    std::ostringstream stream;
    stream << std::boolalpha;
    for (const auto& p : parameters_)
    {
        stream << p.first << '=';
        auto strp = std::get_if<std::string>(&p.second);
        if (strp != nullptr)
            stream << curl_.escape(*strp);
        else
            std::visit([&stream](const auto& val) { stream << val; }, p.second);
        stream << '&';
    }
    auto result = stream.str();
    if (!result.empty())
        result.pop_back();
    return result;
}

std::unique_ptr<cjson::doc> request::run_impl()
{
    std::string url(BASE_URL);
    auto pos = url.find("{}");
    assert(pos != std::string::npos);
    if (is_upload())
        url.replace(pos, 2, "upload/");
    else
        url.erase(pos, 2);
    url += url_stem();
    if (!parameters_.empty())
        url += '?' + parameters_as_url();
    CHUCHO_TRACE_L("Request URL: '" << url << "'");
    curl_.set_option(CURLOPT_URL, url.c_str(), "set URL option");
    return std::move(curl_.perform());
}

delete_request::delete_request(const std::string& access_token)
    : request(access_token)
{
    curl_.set_option(CURLOPT_CUSTOMREQUEST, "DELETE", "set HTTP delete");
}

get_request::get_request(const std::string& access_token)
    : request(access_token)
{
    curl_.set_option(CURLOPT_HTTPGET, 1, "set HTTP get");
}

patch_request::patch_request(const std::string& access_token)
    : post_request(access_token)
{
    curl_.set_option(CURLOPT_POST, 0, "no post");
    curl_.set_option(CURLOPT_CUSTOMREQUEST, "PATCH", "set HTTP patch");
}

post_request::post_request(const std::string& access_token)
    : request(access_token)
{
    curl_.set_option(CURLOPT_POST, 1, "set HTTP post");
}

uploadable_file_request::uploadable_file_request(const std::string& access_token,
                                                 file&& metadata)
    : request(access_token),
      is_upload_(false),
      metadata_(std::move(metadata))
{
}

uploadable_file_request::uploadable_file_request(const std::string& access_token,
                                                 file&& metadata,
                                                 const std::filesystem::path& to_upload)
    : request(access_token),
      is_upload_(false),
      to_upload_(to_upload),
      metadata_(std::move(metadata))
{
}

bool uploadable_file_request::is_upload() const
{
    return is_upload_;
}

std::string uploadable_file_request::metadata_to_json()
{
    auto doc = cJSON_CreateObject();
    metadata_.to_json(*doc);
    auto json = cJSON_PrintUnformatted(doc);
    cJSON_Delete(doc);
    std::string result(json);
    cJSON_free(json);
    return result;
}

std::unique_ptr<cjson::doc> uploadable_file_request::run_impl()
{
    bool is_resumable = false;
    if (to_upload_.empty())
    {
        is_upload_ = false;
        parameters_["uploadType"] = std::string("multipart");
        curl_.post_part("application/json; charset=UTF-8", metadata_to_json());
    }
    else
    {
        is_upload_ = true;
        auto file_size = std::filesystem::file_size(to_upload_);
        // This magic number is 4.5 MB. Google says only do a single
        // upload for files less than 5 MB.
        if (progress_callback_ || file_size > 9 * 1024 * 512)
        {
            is_resumable = true;
            parameters_["uploadType"] = std::string("resumable");
            auto json = metadata_to_json();
            curl_.set_option(CURLOPT_POSTFIELDSIZE, json.length(), "POST field size");
            curl_.set_option(CURLOPT_COPYPOSTFIELDS, json.c_str(), "POST fields");
            if (metadata_.mime_type())
                curl_.header("X-Upload-Content-Type", *metadata_.mime_type());
            curl_.header("X-Upload-Content-Length", std::to_string(file_size));
            curl_.header("Content-Type", "application/json; charset=UTF-8");
            curl_.header("Content-Length", std::to_string(json.length()));
        }
        else
        {
            parameters_["uploadType"] = std::string("multipart");
            curl_.post_part("application/json; charset=UTF-8", metadata_to_json());
            if (file_size > 0)
            {
                std::string mime_type = metadata_.mime_type() ? *metadata_.mime_type() : "application/octet-stream";
                std::ifstream stream(to_upload_, std::ios::in | std::ios::binary);
                std::vector<std::byte> data(file_size);
                stream.read(reinterpret_cast<char*>(data.data()), file_size);
                if (!stream)
                    throw std::runtime_error("Error reading file '" + to_upload_.string() + "'");
                curl_.post_part(mime_type, data);
            }
            else
            {
                is_upload_ = false;
            }
        }
    }
    auto doc = request::run_impl();
    if (is_resumable)
    {
        auto auth = curl_.header("Authorization");
        assert(auth);
        auto loc = curl_.response_header("Location");
        if (!loc)
            throw std::runtime_error("Could not find required header 'Location' in HTTP response");
        resumable_file_upload up(*auth, *loc, to_upload_, progress_callback_);
        doc = up.run();
    }
    return doc;
}

void post_request::to_post(const cJSON& json)
{
    auto str = cJSON_PrintUnformatted(&json);
    auto len = std::strlen(str);
    curl_.header("Content-Type", "application/json; charset=UTF-8");
    curl_.header("Content-Length", std::to_string(len));
    curl_.set_option(CURLOPT_POSTFIELDSIZE, len, "POST field size");
    curl_.set_option(CURLOPT_COPYPOSTFIELDS, str, "copy POST fields");
    cJSON_free(str);
}

}