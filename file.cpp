#include <espadin/file.hpp>
#include "cjson_util.hpp"

namespace espadin
{

file::file(const cJSON& json)
{
    cjson::set_string(json, "kind", kind_);
    cjson::set_string(json, "id", id_);
    cjson::set_string(json, "name", name_);
    cjson::set_string(json, "mimeType", mime_type_);
    cjson::set_string(json, "description", description_);
    cjson::set_bool(json, "starred", starred_);
    cjson::set_bool(json, "trashed", trashed_);
    cjson::set_bool(json, "explicitlyTrashed", explicitly_trashed_);
    cjson::set_object(json, "trashingUser", trashing_user_);
    cjson::set_time(json, "trashedTime", trashed_time_);
    cjson::set_string_vector(json, "parents", parents_);
    cjson::set_map(json, "properties", properties_);
    cjson::set_map(json, "appProperties", app_properties_);
    cjson::set_string_vector(json, "spaces", spaces_);
    cjson::set_number(json, "version", version_);
    cjson::set_string(json, "webContentLink", web_content_link_);
    cjson::set_string(json, "webViewLink", web_view_link_);
    cjson::set_string(json, "iconLink", icon_link_);
    cjson::set_bool(json, "hasThumbnail", has_thumbnail_);
    cjson::set_string(json, "thumbnailLink", thumbnail_link_);
    cjson::set_number(json, "thumbnailVersion", thumbnail_version_);
    cjson::set_bool(json, "viewedByMe", viewed_by_me_);
    cjson::set_time(json, "viewedByMeTime", viewed_by_me_time_);
    cjson::set_time(json, "createdTime", created_time_);
    cjson::set_time(json, "modifiedTime", modified_time_);
    cjson::set_time(json, "modifiedByMeTime", modified_by_me_time_);
    cjson::set_bool(json, "modifiedByMe", modified_by_me_);
    cjson::set_time(json, "sharedWithMeTime", shared_with_me_time_);
    cjson::set_object(json, "sharingUser", sharing_user_);
    cjson::set_object_vector(json, "owners", owners_);
    cjson::set_string(json, "teamDriveId", team_drive_id_);
    cjson::set_string(json, "driveId", drive_id_);
    cjson::set_object(json, "lastModifyingUser", last_modifying_user_);
    cjson::set_bool(json, "shared", shared_);
    cjson::set_bool(json, "ownedByMe", owned_by_me_);
    cjson::set_object(json, "capabilities", capabilities_);
    cjson::set_bool(json, "copyRequiresWriterPermission", copy_requires_writer_permission_);
    cjson::set_bool(json, "writersCanShare", writers_can_share_);
    cjson::set_object_vector(json, "permissions", permissions_);
    cjson::set_string_vector(json, "permissionIds", permission_ids_);
    cjson::set_bool(json, "hasAugmentedPermissions", has_augmented_permissions_);
    cjson::set_string(json, "folderColorRgb", folder_color_rgb_);
    cjson::set_string(json, "originalFileName", original_file_name_);
    cjson::set_string(json, "fullFileExtension", full_file_extension_);
    cjson::set_string(json, "fileExtension", file_extension_);
    cjson::set_string(json, "md5Checksum", md5_checksum_);
    cjson::set_number(json, "size", size_);
    cjson::set_number(json, "quotaBytesUsed", quota_bytes_used_);
    cjson::set_string(json, "headRevisionId", head_revision_id_);
    cjson::set_object(json, "contentHints", content_hints_);
    cjson::set_object(json, "imageMediaMetadata", image_media_metadata_);
    cjson::set_object(json, "videoMediaMetadata", video_media_metadata_);
    cjson::set_bool(json, "isAppAuthorized", is_app_authorized_);
    cjson::set_map(json, "exportLinks", export_links_);
    cjson::set_object(json, "shortcutDetails", shortcut_details_);
    cjson::set_object(json, "contentRestrictions", content_restrictions_);
}

}