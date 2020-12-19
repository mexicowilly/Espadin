#if !defined(ESPADIN_ABOUT_HPP__)
#define ESPADIN_ABOUT_HPP__

#include <espadin/user.hpp>
#include <espadin/storage_quota.hpp>
#include <espadin/drive_theme.hpp>
#include <vector>
#include <map>

namespace espadin
{

class ESPADIN_EXPORT about
{
public:
    about(const cJSON& json);

    const std::optional<bool>& can_create_drives() const;
    const std::optional<bool>& can_create_team_drives() const;
    const std::optional<std::vector<drive_theme>>& drive_themes() const;
    const std::optional<std::map<std::string, std::vector<std::string>>>& export_formats() const;
    const std::optional<storage_quota>& get_storage_quota() const;
    const std::optional<user>& get_user() const;
    const std::optional<std::map<std::string, std::vector<std::string>>>& import_formats() const;
    const std::optional<std::string>& kind() const;
    const std::optional<std::map<std::string, std::size_t>>& max_import_sizes() const;
    const std::optional<std::size_t>& max_upload_size() const;
    const std::optional<std::vector<drive_theme>>& team_drive_themes() const;

private:
    std::optional<std::string> kind_;
    std::optional<user> user_;
    std::optional<storage_quota> storage_quota_;
    std::optional<std::map<std::string, std::vector<std::string>>> import_formats_;
    std::optional<std::map<std::string, std::vector<std::string>>> export_formats_;
    std::optional<std::map<std::string, std::size_t>> max_import_sizes_;
    std::optional<std::size_t> max_upload_size_;
    std::optional<bool> app_installed_;
    std::optional<std::vector<std::string>> folder_color_palette_;
    std::optional<std::vector<drive_theme>> team_drive_themes_;
    std::optional<std::vector<drive_theme>> drive_themes_;
    std::optional<bool> can_create_team_drives_;
    std::optional<bool> can_create_drives_;
};

inline const std::optional<bool>& about::can_create_drives() const
{
    return can_create_drives_;
}

inline const std::optional<bool>& about::can_create_team_drives() const
{
    return can_create_team_drives_;
}

inline const std::optional<std::vector<drive_theme>>& about::drive_themes() const
{
    return drive_themes_;
}

inline const std::optional<std::map<std::string, std::vector<std::string>>>& about::export_formats() const
{
    return export_formats_;
}

inline const std::optional<storage_quota>& about::get_storage_quota() const
{
    return storage_quota_;
}

inline const std::optional<user>& about::get_user() const
{
    return user_;
}

inline const std::optional<std::map<std::string, std::vector<std::string>>>& about::import_formats() const
{
    return import_formats_;
}

inline const std::optional<std::string>& about::kind() const
{
    return kind_;
}

inline const std::optional<std::map<std::string, std::size_t>>& about::max_import_sizes() const
{
    return max_import_sizes_;
}

inline const std::optional<std::size_t>& about::max_upload_size() const
{
    return max_upload_size_;
}

inline const std::optional<std::vector<drive_theme>>& about::team_drive_themes() const
{
    return team_drive_themes_;
}

}

#endif
