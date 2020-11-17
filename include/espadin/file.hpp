#if !defined(ESPADIN_FILE_HPP__)
#define ESPADIN_FILE_HPP__

#include <espadin/user.hpp>
#include <espadin/permission.hpp>
#include <espadin/capabilities.hpp>
#include <espadin/image_media_metadata.hpp>
#include <espadin/video_media_metadata.hpp>
#include <espadin/content_hints.hpp>
#include <espadin/shortcut_details.hpp>
#include <espadin/content_restrictions.hpp>
#include <map>

namespace espadin
{

class ESPADIN_EXPORT file
{
public:
    file(const cJSON& json);

    const std::optional<std::map<std::string, std::string>>& app_properties() const;
    const std::optional<bool>& copy_requires_writer_permission() const;
    const std::optional<std::chrono::system_clock::time_point>& created_time() const;
    const std::optional<std::string>& description() const;
    const std::optional<std::string>& drive_id() const;
    const std::optional<bool>& explicitly_trashed() const;
    const std::optional<std::map<std::string, std::string>>& export_links() const;
    const std::optional<std::string>& file_extension() const;
    const std::optional<std::string>& folder_color_rgb() const;
    const std::optional<std::string>& full_file_extension() const;
    const std::optional<capabilities>& get_capabilities() const;
    const std::optional<content_hints>& get_content_hints() const;
    const std::optional<content_restrictions>& get_content_restrictions() const;
    const std::optional<image_media_metadata>& get_image_media_metadata() const;
    const std::optional<shortcut_details>& get_shortcut_details() const;
    const std::optional<video_media_metadata>& get_video_media_metadata() const;
    const std::optional<std::string>& kind() const;
    const std::optional<bool>& has_augmented_permissions() const;
    const std::optional<bool>& has_thumbnail() const;
    const std::optional<std::string>& head_revision_id() const;
    const std::optional<std::string>& icon_link() const;
    const std::optional<std::string>& id() const;
    const std::optional<bool>& is_app_authorized() const;
    const std::optional<user>& last_modifying_user() const;
    const std::optional<std::string>& md5_checksum() const;
    const std::optional<std::string>& name() const;
    const std::optional<std::string>& mime_type() const;
    const std::optional<bool>& modified_by_me() const;
    const std::optional<std::chrono::system_clock::time_point>& modified_by_me_time() const;
    const std::optional<std::chrono::system_clock::time_point>& modified_time() const;
    const std::optional<std::string>& original_file_name() const;
    const std::optional<bool>& owned_by_me() const;
    const std::optional<std::vector<user>>& owners() const;
    const std::optional<std::vector<std::string>>& parents() const;
    const std::optional<std::vector<std::string>>& permission_ids() const;
    const std::optional<std::vector<permission>>& permissions() const;
    const std::optional<std::map<std::string, std::string>>& properties() const;
    const std::optional<std::size_t>& quota_bytes_used() const;
    const std::optional<bool>& shared() const;
    const std::optional<std::chrono::system_clock::time_point>& shared_with_me_time() const;
    const std::optional<user>& sharing_user() const;
    const std::optional<std::size_t>& size() const;
    const std::optional<std::vector<std::string>>& spaces() const;
    const std::optional<bool>& starred() const;
    const std::optional<std::string>& team_drive_id() const;
    const std::optional<std::string>& thumbnail_link() const;
    const std::optional<long>& thumbnail_version() const;
    const std::optional<bool>& trashed() const;
    const std::optional<std::chrono::system_clock::time_point>& trashed_time() const;
    const std::optional<user>& trashing_user() const;
    const std::optional<long>& version() const;
    const std::optional<bool>& viewed_by_me() const;
    const std::optional<std::chrono::system_clock::time_point>& viewed_by_me_time() const;
    const std::optional<std::string>& web_content_link() const;
    const std::optional<std::string>& web_view_link() const;
    const std::optional<bool>& writers_can_share() const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> id_;
    std::optional<std::string> name_;
    std::optional<std::string> mime_type_;
    std::optional<std::string> description_;
    std::optional<bool> starred_;
    std::optional<bool> trashed_;
    std::optional<bool> explicitly_trashed_;
    std::optional<user> trashing_user_;
    std::optional<std::chrono::system_clock::time_point> trashed_time_;
    std::optional<std::vector<std::string>> parents_;
    std::optional<std::map<std::string, std::string>> properties_;
    std::optional<std::map<std::string, std::string>> app_properties_;
    std::optional<std::vector<std::string>> spaces_;
    std::optional<long> version_;
    std::optional<std::string> web_content_link_;
    std::optional<std::string> web_view_link_;
    std::optional<std::string> icon_link_;
    std::optional<bool> has_thumbnail_;
    std::optional<std::string> thumbnail_link_;
    std::optional<long> thumbnail_version_;
    std::optional<bool> viewed_by_me_;
    std::optional<std::chrono::system_clock::time_point> viewed_by_me_time_;
    std::optional<std::chrono::system_clock::time_point> created_time_;
    std::optional<std::chrono::system_clock::time_point> modified_time_;
    std::optional<std::chrono::system_clock::time_point> modified_by_me_time_;
    std::optional<bool> modified_by_me_;
    std::optional<std::chrono::system_clock::time_point> shared_with_me_time_;
    std::optional<user> sharing_user_;
    std::optional<std::vector<user>> owners_;
    std::optional<std::string> team_drive_id_;
    std::optional<std::string> drive_id_;
    std::optional<user> last_modifying_user_;
    std::optional<bool> shared_;
    std::optional<bool> owned_by_me_;
    std::optional<capabilities> capabilities_;
    std::optional<bool> copy_requires_writer_permission_;
    std::optional<bool> writers_can_share_;
    std::optional<std::vector<permission>> permissions_;
    std::optional<std::vector<std::string>> permission_ids_;
    std::optional<bool> has_augmented_permissions_;
    std::optional<std::string> folder_color_rgb_;
    std::optional<std::string> original_file_name_;
    std::optional<std::string> full_file_extension_;
    std::optional<std::string> file_extension_;
    std::optional<std::string> md5_checksum_;
    std::optional<std::size_t> size_;
    std::optional<std::size_t> quota_bytes_used_;
    std::optional<std::string> head_revision_id_;
    std::optional<content_hints> content_hints_;
    std::optional<image_media_metadata> image_media_metadata_;
    std::optional<video_media_metadata> video_media_metadata_;
    std::optional<bool> is_app_authorized_;
    std::optional<std::map<std::string, std::string>> export_links_;
    std::optional<shortcut_details> shortcut_details_;
    std::optional<content_restrictions> content_restrictions_;
};

inline const std::optional<std::map<std::string, std::string>>& file::app_properties() const
{
    return app_properties_;
}

inline const std::optional<bool>& file::copy_requires_writer_permission() const
{
    return copy_requires_writer_permission_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::created_time() const
{
    return created_time_;
}

inline const std::optional<std::string>& file::description() const
{
    return description_;
}

inline const std::optional<std::string>& file::drive_id() const
{
    return drive_id_;
}

inline const std::optional<bool>& file::explicitly_trashed() const
{
    return explicitly_trashed_;
}

inline const std::optional<std::map<std::string, std::string>>& file::export_links() const
{
    return export_links_;
}

inline const std::optional<std::string>& file::file_extension() const
{
    return file_extension_;
}

inline const std::optional<std::string>& file::folder_color_rgb() const
{
    return folder_color_rgb_;
}

inline const std::optional<std::string>& file::full_file_extension() const
{
    return full_file_extension_;
}

inline const std::optional<capabilities>& file::get_capabilities() const
{
    return capabilities_;
}

inline const std::optional<content_hints>& file::get_content_hints() const
{
    return content_hints_;
}

inline const std::optional<content_restrictions>& file::get_content_restrictions() const
{
    return content_restrictions_;
}

inline const std::optional<image_media_metadata>& file::get_image_media_metadata() const
{
    return image_media_metadata_;
}

inline const std::optional<shortcut_details>& file::get_shortcut_details() const
{
    return shortcut_details_;
}

inline const std::optional<video_media_metadata>& file::get_video_media_metadata() const
{
    return video_media_metadata_;
}

inline const std::optional<std::string>& file::kind() const
{
    return kind_;
}

inline const std::optional<bool>& file::has_augmented_permissions() const
{
    return has_augmented_permissions_;
}

inline const std::optional<bool>& file::has_thumbnail() const
{
    return has_thumbnail_;
}

inline const std::optional<std::string>& file::head_revision_id() const
{
    return head_revision_id_;
}

inline const std::optional<std::string>& file::icon_link() const
{
    return icon_link_;
}

inline const std::optional<std::string>& file::id() const
{
    return id_;
}

inline const std::optional<bool>& file::is_app_authorized() const
{
    return is_app_authorized_;
}

inline const std::optional<user>& file::last_modifying_user() const
{
    return last_modifying_user_;
}

inline const std::optional<std::string>& file::md5_checksum() const
{
    return md5_checksum_;
}

inline const std::optional<std::string>& file::name() const
{
    return name_;
}

inline const std::optional<std::string>& file::mime_type() const
{
    return mime_type_;
}

inline const std::optional<bool>& file::modified_by_me() const
{
    return modified_by_me_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::modified_by_me_time() const
{
    return modified_by_me_time_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::modified_time() const
{
    return modified_time_;
}

inline const std::optional<std::string>& file::original_file_name() const
{
    return original_file_name_;
}

inline const std::optional<bool>& file::owned_by_me() const
{
    return owned_by_me_;
}

inline const std::optional<std::vector<user>>& file::owners() const
{
    return owners_;
}

inline const std::optional<std::vector<std::string>>& file::parents() const
{
    return parents_;
}

inline const std::optional<std::vector<std::string>>& file::permission_ids() const
{
    return permission_ids_;
}

inline const std::optional<std::vector<permission>>& file::permissions() const
{
    return permissions_;
}

inline const std::optional<std::map<std::string, std::string>>& file::properties() const
{
    return properties_;
}

inline const std::optional<std::size_t>& file::quota_bytes_used() const
{
    return quota_bytes_used_;
}

inline const std::optional<bool>& file::shared() const
{
    return shared_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::shared_with_me_time() const
{
    return shared_with_me_time_;
}

inline const std::optional<user>& file::sharing_user() const
{
    return sharing_user_;
}

inline const std::optional<std::size_t>& file::size() const
{
    return size_;
}

inline const std::optional<std::vector<std::string>>& file::spaces() const
{
    return spaces_;
}

inline const std::optional<bool>& file::starred() const
{
    return starred_;
}

inline const std::optional<std::string>& file::team_drive_id() const
{
    return team_drive_id_;
}

inline const std::optional<std::string>& file::thumbnail_link() const
{
    return thumbnail_link_;
}

inline const std::optional<long>& file::thumbnail_version() const
{
    return thumbnail_version_;
}

inline const std::optional<bool>& file::trashed() const
{
    return trashed_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::trashed_time() const
{
    return trashed_time_;
}

inline const std::optional<user>& file::trashing_user() const
{
    return trashing_user_;
}

inline const std::optional<long>& file::version() const
{
    return version_;
}

inline const std::optional<bool>& file::viewed_by_me() const
{
    return viewed_by_me_;
}

inline const std::optional<std::chrono::system_clock::time_point>& file::viewed_by_me_time() const
{
    return viewed_by_me_time_;
}

inline const std::optional<std::string>& file::web_content_link() const
{
    return web_content_link_;
}

inline const std::optional<std::string>& file::web_view_link() const
{
    return web_view_link_;
}

inline const std::optional<bool>& file::writers_can_share() const
{
    return writers_can_share_;
}

}

#endif
