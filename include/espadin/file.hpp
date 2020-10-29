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

private:
    std::string kind_;
    std::string id_;
    std::string name_;
    std::string mime_type_;
    std::string description_;
    bool starred_;
    bool trashed_;
    bool explicitly_trashed_;
    std::optional<user> trashing_user_;
    std::chrono::system_clock::time_point trashed_time_;
    std::vector<std::string> parents_;
    std::map<std::string, std::string> properties_;
    std::map<std::string, std::string> app_properties_;
    std::vector<std::string> spaces_;
    long version_;
    std::string web_content_link_;
    std::string web_view_link_;
    std::string icon_link_;
    bool has_thumbnail_;
    std::string thumbnail_link_;
    long thumbnail_version_;
    bool viewed_by_me_;
    std::chrono::system_clock::time_point viewed_by_me_time_;
    std::chrono::system_clock::time_point created_time_;
    std::chrono::system_clock::time_point modified_time_;
    std::chrono::system_clock::time_point modified_by_me_time_;
    bool modified_by_me_;
    std::chrono::system_clock::time_point shared_with_me_time_;
    std::optional<user> sharing_user_;
    std::vector<user> owners_;
    std::string team_drive_id_;
    std::string drive_id_;
    std::optional<user> last_modifying_user_;
    bool shared_;
    bool owned_by_me_;
    std::optional<capabilities> capabilities_;
    bool copy_requires_writer_permission_;
    bool writers_can_share_;
    std::vector<permission> permissions_;
    std::vector<std::string> permission_ids_;
    bool has_augmented_permissions_;
    std::string folder_color_rgb_;
    std::string original_file_name_;
    std::string full_file_extension_;
    std::string file_extension_;
    std::string md5_checksum_;
    long size_;
    long quota_bytes_used_;
    std::string head_revision_id_;
    std::optional<content_hints> content_hints_;
    std::optional<image_media_metadata> image_media_metadata_;
    std::optional<video_media_metadata> video_media_metadata_;
    bool is_app_authorized_;
    std::map<std::string, std::string> export_links_;
    std::optional<shortcut_details> shortcut_details_;
    std::optional<content_restrictions> content_restrictions_;
};

}

#endif
