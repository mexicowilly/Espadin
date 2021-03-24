#if !defined(ESPADIN_ACCESS_TOKEN_ACCESSOR_HPP__)
#define ESPADIN_ACCESS_TOKEN_ACCESSOR_HPP__

#include <functional>

namespace espadin
{

class access_token_accessor
{
public:
    access_token_accessor(const access_token_accessor&) = delete;
    access_token_accessor& operator= (const access_token_accessor&) = delete;

protected:
    using access_token_function = std::function<const std::string&()>;

    access_token_accessor(access_token_function func);

    access_token_function access_token_;
};

inline access_token_accessor::access_token_accessor(access_token_function func)
    : access_token_(func)
{
}

}

#endif
