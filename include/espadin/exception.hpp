#if !defined(ESPADIN_EXCEPTION_HPP__)
#define ESPADIN_EXCEPTION_HPP__

#include <espadin/export.hpp>
#include <exception>
#include <map>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT exception : public std::exception
{
public:
    exception(const cJSON& json);

    int code() const;
    const std::map<std::string, std::string>& errors() const;
    virtual const char* what() const noexcept override;

private:
    int code_;
    std::string message_;
    std::map<std::string, std::string> errors_;
};

std::ostream& operator<< (std::ostream& stream, const exception& excp);

inline int exception::code() const
{
    return code_;
}

inline const std::map<std::string, std::string>& exception::errors() const
{
    return errors_;
}

}

#endif
