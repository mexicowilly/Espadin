#if !defined(ESPADING_USER_HPP__)
#define ESPADING_USER_HPP__

#include <espadin/export.hpp>
#include <string>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT user
{
public:
    user(const cJSON& json);

    const std::string& display_name() const;
    const std::string& email_address() const;
    const std::string& kind() const;
    bool me() const;
    const std::string& permission_id() const;
    const std::string& photo_link() const;

private:
    std::string kind_;
    std::string display_name_;
    std::string photo_link_;
    bool me_;
    std::string permission_id_;
    std::string email_address_;
};

inline const std::string& user::display_name() const
{
    return display_name_;
}

inline const std::string& user::email_address() const
{
    return email_address_;
}

inline const std::string& user::kind() const
{
    return kind_;
}

inline bool user::me() const
{
    return me_;
}

inline const std::string& user::permission_id() const
{
    return permission_id_;
}

inline const std::string& user::photo_link() const
{
    return photo_link_;
}

}

#endif