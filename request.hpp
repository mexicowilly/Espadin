#if !defined (ESPADIN_REQUEST_HPP__)
#define ESPADIN_REQUEST_HPP__

#include <chucho/loggable.hpp>
#include <variant>
#include <map>
#include "curl.hpp"

namespace espadin
{

class request : public chucho::loggable<request>
{
public:
    virtual ~request();


protected:
    using variant_type = std::variant<std::string, int, bool, std::size_t>;

    request(const std::string& access_token);

    std::unique_ptr<cjson::doc> run_impl();
    virtual std::string url_stem() const = 0;

    std::map<std::string, variant_type> parameters_;
    curl curl_;

private:
    static const std::string BASE_URL;

    std::string parameters_as_url() const;
};

class get_request : public request
{
protected:
    get_request(const std::string& access_token);
};

class post_request : public request
{
protected:
    post_request(const std::string& access_token);
};

}

#endif