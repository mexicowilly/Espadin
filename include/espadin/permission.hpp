#if !defined(ESPADIN_PERMISSION_HPP__)
#define ESPADIN_PERMISSION_HPP__

#include <espadin/export.hpp>
#include <string>
#include <chrono>
#include <vector>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT permission
{
public:
    class details
    {
    public:
        details(const cJSON& json);

        bool inherited() const;
        const std::string& inherited_from() const;
        const std::string& permision_type() const;
        const std::string& role() const;

    private:
        std::string permission_type_;
        std::string role_;
        std::string inherited_from_;
        bool inherited_;
    };

    permission(const cJSON& json);

    bool allow_file_discovery() const;
    bool deleted() const;
    const std::string& display_name() const;
    const std::string& domain() const;
    const std::string& email_address() const;
    const std::chrono::system_clock::time_point& expiration_time() const;
    const std::string& kind() const;
    const std::string& id() const;
    const std::vector<details> permission_details() const;
    const std::string& photo_link() const;
    const std::string& role() const;
    const std::string& type() const;
    const std::string& view() const;

private:
    std::string kind_;
    std::string id_;
    std::string type_;
    std::string email_address_;
    std::string domain_;
    std::string role_;
    std::string view_;
    std::string display_name_;
    std::string photo_link_;
    bool allow_file_discovery_;
    std::chrono::system_clock::time_point expiration_time_;
    bool deleted_;
    std::vector<details> permission_details_;
};

inline bool permission::allow_file_discovery() const
{
    return allow_file_discovery_;
}

inline bool permission::deleted() const
{
    return deleted_;
}

inline const std::string& permission::display_name() const
{
    return display_name_;
}

inline const std::string& permission::domain() const
{
    return domain_;
}

inline const std::string& permission::email_address() const
{
    return email_address_;
}

inline const std::chrono::system_clock::time_point& permission::expiration_time() const
{
    return expiration_time_;
}

inline const std::string& permission::kind() const
{
    return kind_;
}

inline const std::string& permission::id() const
{
    return id_;
}

inline const std::vector<permission::details> permission::permission_details() const
{
    return permission_details_;
}

inline const std::string& permission::photo_link() const
{
    return photo_link_;
}

inline const std::string& permission::role() const
{
    return role_;
}

inline const std::string& permission::type() const
{
    return type_;
}

inline const std::string& permission::view() const
{
    return view_;
}

inline bool permission::details::inherited() const
{
    return inherited_;
}

inline const std::string& permission::details::inherited_from() const
{
    return inherited_from_;
}

inline const std::string& permission::details::permision_type() const
{
    return permission_type_;
}

inline const std::string& permission::details::role() const
{
    return role_;
}

}

#endif