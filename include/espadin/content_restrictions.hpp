#if !defined(ESPADIN_CONTENT_RESTRICTIONS_HPP__)
#define ESPADIN_CONTENT_RESTRICTIONS_HPP__

#include <espadin/user.hpp>
#include <optional>
#include <chrono>

namespace espadin
{

class ESPADIN_EXPORT content_restrictions
{
public:
    content_restrictions(const cJSON& json);

    bool read_only() const;
    const std::string& reason() const;
    const std::optional<user>& restricting_user() const;
    const std::chrono::system_clock::time_point& restriction_time() const;
    const std::string& type() const;

private:
    bool read_only_;
    std::string reason_;
    std::optional<user> restricting_user_;
    std::chrono::system_clock::time_point restriction_time_;
    std::string type_;
};

inline bool content_restrictions::read_only() const
{
    return read_only_;
}

inline const std::string& content_restrictions::reason() const
{
    return reason_;
}

inline const std::optional<user>& content_restrictions::restricting_user() const
{
    return restricting_user_;
}

inline const std::chrono::system_clock::time_point& content_restrictions::restriction_time() const
{
    return restriction_time_;
}

inline const std::string& content_restrictions::type() const
{
    return type_;
}

}

#endif