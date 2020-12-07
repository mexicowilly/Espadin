#if !defined(ESPADIN_EXCEPTION_HPP__)
#define ESPADIN_EXCEPTION_HPP__

#include <espadin/export.hpp>
#include <exception>
#include <map>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT drive_exception : public std::exception
{
public:
    drive_exception(const cJSON& json);

    int code() const;
    const std::map<std::string, std::string>& errors() const;
    virtual const char* what() const noexcept override;

private:
    int code_;
    std::string message_;
    std::map<std::string, std::string> errors_;
};

std::ostream& operator<< (std::ostream& stream, const drive_exception& excp);

class ESPADIN_EXPORT http_exception : public std::runtime_error
{
public:
    http_exception(long code);

    long code() const;

private:
    long code_;
};

inline int drive_exception::code() const
{
    return code_;
}

inline const std::map<std::string, std::string>& drive_exception::errors() const
{
    return errors_;
}

inline long http_exception::code() const
{
    return code_;
}

}

#endif
