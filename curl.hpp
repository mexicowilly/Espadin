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

namespace espadin
{

class ESPADIN_PRIV_EXPORT curl : public chucho::loggable<curl>
{
public:
    static bool get_ssl_supported();

    curl();
    virtual ~curl();

    curl_slist* create_slist(std::vector<std::string>&& items0);
    std::string escape(const std::string& str) const;
    std::unique_ptr<cjson::doc> perform();
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

    CURL* curl_;
    bool verbose_;
    std::vector<std::unique_ptr<curl_slist, void(*)(curl_slist*)>> slists_;
};

template<typename arg_type>
void curl::set_option(CURLoption opt, arg_type arg, const char* const err_msg)
{
    CURLcode rc = curl_easy_setopt(curl_, opt, arg);
    if (rc != CURLE_OK)
        throw curl_exception(rc, std::string("Could not set CURL option: ") + err_msg);
}

}

#endif