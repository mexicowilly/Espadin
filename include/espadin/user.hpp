#if !defined(ESPADING_USER_HPP_)
#define ESPADING_USER_HPP_

#include <espadin/export.hpp>
#include <string>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT user
{
public:
    user(const cJSON& json);

    const std::optional<std::string>& display_name() const;
    const std::optional<std::string>& email_address() const;
    const std::optional<std::string>& kind() const;
    const std::optional<bool>& me() const;
    const std::optional<std::string>& permission_id() const;
    const std::optional<std::string>& photo_link() const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> display_name_;
    std::optional<std::string> photo_link_;
    std::optional<bool> me_;
    std::optional<std::string> permission_id_;
    std::optional<std::string> email_address_;
};

inline const std::optional<std::string>& user::display_name() const
{
    return display_name_;
}

inline const std::optional<std::string>& user::email_address() const
{
    return email_address_;
}

inline const std::optional<std::string>& user::kind() const
{
    return kind_;
}

inline const std::optional<bool>& user::me() const
{
    return me_;
}

inline const std::optional<std::string>& user::permission_id() const
{
    return permission_id_;
}

inline const std::optional<std::string>& user::photo_link() const
{
    return photo_link_;
}

}

#endif