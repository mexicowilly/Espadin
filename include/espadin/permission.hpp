#if !defined(ESPADIN_PERMISSION_HPP__)
#define ESPADIN_PERMISSION_HPP__

#include <espadin/export.hpp>
#include <string>
#include <chrono>
#include <vector>
#include <optional>

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

        const std::optional<bool>& inherited() const;
        const std::optional<std::string>& inherited_from() const;
        const std::optional<std::string>& permision_type() const;
        const std::optional<std::string>& role() const;

    private:
        std::optional<std::string> permission_type_;
        std::optional<std::string> role_;
        std::optional<std::string> inherited_from_;
        std::optional<bool> inherited_;
    };

    permission(const cJSON& json);

    const std::optional<bool>& allow_file_discovery() const;
    const std::optional<bool>& deleted() const;
    const std::optional<std::string>& display_name() const;
    const std::optional<std::string>& domain() const;
    const std::optional<std::string>& email_address() const;
    const std::optional<std::chrono::system_clock::time_point>& expiration_time() const;
    const std::optional<std::string>& kind() const;
    const std::optional<std::string>& id() const;
    const std::optional<std::vector<details>>& permission_details() const;
    const std::optional<std::string>& photo_link() const;
    const std::optional<std::string>& role() const;
    const std::optional<std::string>& type() const;
    const std::optional<std::string>& view() const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> id_;
    std::optional<std::string> type_;
    std::optional<std::string> email_address_;
    std::optional<std::string> domain_;
    std::optional<std::string> role_;
    std::optional<std::string> view_;
    std::optional<std::string> display_name_;
    std::optional<std::string> photo_link_;
    std::optional<bool> allow_file_discovery_;
    std::optional<std::chrono::system_clock::time_point> expiration_time_;
    std::optional<bool> deleted_;
    std::optional<std::vector<details>> permission_details_;
};

inline const std::optional<bool>& permission::allow_file_discovery() const
{
    return allow_file_discovery_;
}

inline const std::optional<bool>& permission::deleted() const
{
    return deleted_;
}

inline const std::optional<std::string>& permission::display_name() const
{
    return display_name_;
}

inline const std::optional<std::string>& permission::domain() const
{
    return domain_;
}

inline const std::optional<std::string>& permission::email_address() const
{
    return email_address_;
}

inline const std::optional<std::chrono::system_clock::time_point>& permission::expiration_time() const
{
    return expiration_time_;
}

inline const std::optional<std::string>& permission::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& permission::id() const
{
    return id_;
}

inline const std::optional<std::vector<permission::details>>& permission::permission_details() const
{
    return permission_details_;
}

inline const std::optional<std::string>& permission::photo_link() const
{
    return photo_link_;
}

inline const std::optional<std::string>& permission::role() const
{
    return role_;
}

inline const std::optional<std::string>& permission::type() const
{
    return type_;
}

inline const std::optional<std::string>& permission::view() const
{
    return view_;
}

inline const std::optional<bool>& permission::details::inherited() const
{
    return inherited_;
}

inline const std::optional<std::string>& permission::details::inherited_from() const
{
    return inherited_from_;
}

inline const std::optional<std::string>& permission::details::permision_type() const
{
    return permission_type_;
}

inline const std::optional<std::string>& permission::details::role() const
{
    return role_;
}

}

#endif