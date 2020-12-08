#ifndef ESPADIN_CURL_HPP__
#define ESPADIN_CURL_HPP__

#include <espadin/export.hpp>
#include "cjson_doc.hpp"
#include <chucho/loggable.hpp>
#include <curl/curl.h>
#include <cstdint>
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <map>
#include <variant>

namespace espadin
{

class ESPADIN_PRIV_EXPORT curl : public chucho::loggable<curl>
{
public:
    static bool ssl_supported();

    curl();
    virtual ~curl();

    std::string escape(const std::string& str) const;
    std::optional<std::string> header(const std::string& key);
    void header(const std::string& name, const std::string& value);
    std::unique_ptr<cjson::doc> perform();
    void post_part(const std::string& mime_type, const std::string& data);
    void post_part(const std::string& mime_type, const std::vector<std::byte>& data);
    long response_code() const;
    std::optional<std::string> response_header(const std::string& key);
    template<typename arg_type>
    void set_option(CURLoption opt, arg_type arg, const char* const err_msg);
    void set_verbose(bool state);

private:
    class ESPADIN_NO_EXPORT curl_exception : public std::runtime_error
    {
    public:
        curl_exception(CURLcode err, const std::string& msg);
    };

    friend ESPADIN_NO_EXPORT int curl_debug_callback(CURL* crl,
                                                     curl_infotype info_type,
                                                     char* text,
                                                     std::size_t num,
                                                     void* user_data);

    void maybe_set_post_parts(std::vector<char>& result);

    CURL* curl_;
    bool verbose_;
    std::map<std::string, std::string> headers_;
    std::vector<std::tuple<std::string, std::variant<std::string, std::vector<std::byte>>>> post_parts_;
    std::map<std::string, std::string> response_headers_;
    long response_code_;
};

inline void curl::header(const std::string& name, const std::string& value)
{
    headers_[name] = value;
}

inline void curl::post_part(const std::string& mime_type, const std::string& data)
{
    post_parts_.emplace_back(mime_type, data);
}

inline void curl::post_part(const std::string& mime_type, const std::vector<std::byte>& data)
{
    post_parts_.emplace_back(mime_type, data);
}

inline long curl::response_code() const
{
    return response_code_;
}

template<typename arg_type>
void curl::set_option(CURLoption opt, arg_type arg, const char* const err_msg)
{
    CURLcode rc = curl_easy_setopt(curl_, opt, arg);
    if (rc != CURLE_OK)
        throw curl_exception(rc, std::string("Could not set CURL option: ") + err_msg);
}

}

#endif