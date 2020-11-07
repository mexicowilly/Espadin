#include "request.hpp"
#include <espadin/exception.hpp>
#include <sstream>

namespace espadin
{

const std::string request::BASE_URL("https://www.googleapis.com/drive/v3/");

request::request(const std::string& access_token)
{
    curl_.set_option(CURLOPT_XOAUTH2_BEARER, access_token.c_str(), "set Oauth2 bearer");
}

request::~request()
{
}

std::string request::parameters_as_url() const
{
    std::ostringstream stream;
    stream << std::boolalpha;
    for (const auto& p : parameters_)
    {
        stream << p.first << '=';
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
    std::string url(BASE_URL + url_stem());
    if (!parameters_.empty())
    {
        url += '?';
        url += parameters_as_url();
    }
    auto esc = curl_.escape(url);
    curl_.set_option(CURLOPT_URL, esc.c_str(), "set URL option");
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

}