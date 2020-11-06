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

    std::unique_ptr<cjson::doc> run();

protected:
    using variant_type = std::variant<std::string, int>;

    request(const std::string& access_token);
    virtual std::string url_stem() const = 0;

    std::map<std::string, variant_type> parameters_;

    curl curl_;

private:
    static const std::string BASE_URL;

    std::string parameters_as_url() const;
};

class get_request : public request
{
public:
    get_request(const std::string& access_token);
};

}

#endif