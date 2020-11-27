#include "request.hpp"
#include <espadin/exception.hpp>
#include <chucho/log.hpp>
#include <sstream>
#include <cassert>

namespace
{

const std::string BASE_URL("https://www.googleapis.com/{}drive/v3/");

}

namespace espadin
{

request::request(const std::string& access_token)
{
    curl_.header("Authorization", "Bearer " + access_token);
//    std::string auth("Authorization: Bearer " + access_token);
//    auto head = curl_.create_slist({auth});
//    curl_.set_option(CURLOPT_HTTPHEADER, head, "HTTP authorization header");
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
    auto result = curl_.perform();
    if (cJSON_HasObjectItem(**result, "error"))
        throw exception(***result);
    return std::move(result);
}

get_request::get_request(const std::string& access_token)
    : request(access_token)
{
    curl_.set_option(CURLOPT_HTTPGET, 1, "set HTTP get");
}

post_request::post_request(const std::string& access_token)
    : request(access_token)
{
    curl_.set_option(CURLOPT_POST, 1, "set HTTP post");
}

}