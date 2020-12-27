#if !defined(ESPADIN_REPLY_HPP__)
#define ESPADIN_REPLY_HPP__

#include <espadin/user.hpp>
#include <chrono>

namespace espadin
{

class ESPADIN_EXPORT reply
{
public:
    reply() = default;
    reply(const cJSON& json);

    const std::optional<std::string>& action() const;
    reply& action(const std::string& str);
    const std::optional<user>& author() const;
    const std::optional<std::string>& content() const;
    reply& content(const std::string& str);
    const std::optional<std::chrono::system_clock::time_point>& created_time() const;
    const std::optional<bool>& deleted() const;
    const std::optional<std::string>& html_content() const;
    const std::optional<std::string>& id() const;
    const std::optional<std::string>& kind() const;
    const std::optional<std::chrono::system_clock::time_point>& modified_time() const;
    void to_json(cJSON& json) const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> id_;
    std::optional<std::chrono::system_clock::time_point> created_time_;
    std::optional<std::chrono::system_clock::time_point> modified_time_;
    std::optional<user> author_;
    std::optional<std::string> html_content_;
    std::optional<std::string> content_;
    std::optional<bool> deleted_;
    std::optional<std::string> action_;
};

inline const std::optional<std::string>& reply::action() const
{
    return action_;
}

inline reply& reply::action(const std::string& str)
{
    action_ = str;
    return *this;
}

inline const std::optional<user>& reply::author() const
{
    return author_;
}

inline const std::optional<std::string>& reply::content() const
{
    return content_;
}

inline reply& reply::content(const std::string& str)
{
    content_ = str;
    return *this;
}

inline const std::optional<std::chrono::system_clock::time_point>& reply::created_time() const
{
    return created_time_;
}

inline const std::optional<bool>& reply::deleted() const
{
    return deleted_;
}

inline const std::optional<std::string>& reply::html_content() const
{
    return html_content_;
}

inline const std::optional<std::string>& reply::id() const
{
    return id_;
}

inline const std::optional<std::string>& reply::kind() const
{
    return kind_;
}

inline const std::optional<std::chrono::system_clock::time_point>& reply::modified_time() const
{
    return modified_time_;
}

}

#endif
