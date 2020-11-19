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
    content_restrictions() = default;
    content_restrictions(const cJSON& json);

    const std::optional<bool>& read_only() const;
    content_restrictions& read_only(bool to_set);
    const std::optional<std::string>& reason() const;
    content_restrictions& reason(const std::string& txt);
    const std::optional<user>& restricting_user() const;
    const std::optional<std::chrono::system_clock::time_point>& restriction_time() const;
    void to_json(cJSON& json) const;
    const std::optional<std::string>& type() const;

private:
    std::optional<bool> read_only_;
    std::optional<std::string> reason_;
    std::optional<user> restricting_user_;
    std::optional<std::chrono::system_clock::time_point> restriction_time_;
    std::optional<std::string> type_;
};

inline const std::optional<bool>& content_restrictions::read_only() const
{
    return read_only_;
}

inline content_restrictions& content_restrictions::read_only(bool to_set)
{
    read_only_ = to_set;
    return *this;
}

inline const std::optional<std::string>& content_restrictions::reason() const
{
    return reason_;
}

inline content_restrictions& content_restrictions::reason(const std::string& txt)
{
    reason_ = txt;
    return *this;
}

inline const std::optional<user>& content_restrictions::restricting_user() const
{
    return restricting_user_;
}

inline const std::optional<std::chrono::system_clock::time_point>& content_restrictions::restriction_time() const
{
    return restriction_time_;
}

inline const std::optional<std::string>& content_restrictions::type() const
{
    return type_;
}

}

#endif