#include <espadin/about.hpp>
#include "cjson_util.hpp"

namespace espadin
{

about::about(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_object("user", user_);
    ju.set_object("storageQuota", storage_quota_);
    ju.set_map_of_string_array("importFormats", import_formats_);
    ju.set_map_of_string_array("exportFormats", export_formats_);
    std::optional<std::map<std::string, std::string>> scratch;
    ju.set_map("maxImportSizes", scratch);
    if (scratch && !scratch->empty())
    {
        max_import_sizes_.emplace();
        for (const auto& p : *scratch)
            max_import_sizes_->emplace(p.first, std::stoul(p.second));
    }
    ju.set_number("maxUploadSize", max_upload_size_);
    ju.set_bool("appInstalled", app_installed_);
    ju.set_string_vector("folderColorPalette", folder_color_palette_);
    ju.set_object_vector("teamDriveThemes", team_drive_themes_);
    ju.set_object_vector("driveThemes", drive_themes_);
    ju.set_bool("canCreateTeamDrives", can_create_team_drives_);
    ju.set_bool("canCreateDrives", can_create_drives_);
}

}