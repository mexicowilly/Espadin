#include <espadin/file.hpp>
#include "cjson_util.hpp"

namespace espadin
{

file::file(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("id", id_);
    ju.set_string("name", name_);
    ju.set_string("mimeType", mime_type_);
    ju.set_string("description", description_);
    ju.set_bool("starred", starred_);
    ju.set_bool("trashed", trashed_);
    ju.set_bool("explicitlyTrashed", explicitly_trashed_);
    ju.set_object("trashingUser", trashing_user_);
    ju.set_time("trashedTime", trashed_time_);
    ju.set_string_vector("parents", parents_);
    ju.set_map("properties", properties_);
    ju.set_map("appProperties", app_properties_);
    ju.set_string_vector("spaces", spaces_);
    ju.set_number_from_string("version", version_);
    ju.set_string("webContentLink", web_content_link_);
    ju.set_string("webViewLink", web_view_link_);
    ju.set_string("iconLink", icon_link_);
    ju.set_bool("hasThumbnail", has_thumbnail_);
    ju.set_string("thumbnailLink", thumbnail_link_);
    ju.set_number_from_string("thumbnailVersion", thumbnail_version_);
    ju.set_bool("viewedByMe", viewed_by_me_);
    ju.set_time("viewedByMeTime", viewed_by_me_time_);
    ju.set_time("createdTime", created_time_);
    ju.set_time("modifiedTime", modified_time_);
    ju.set_time("modifiedByMeTime", modified_by_me_time_);
    ju.set_bool("modifiedByMe", modified_by_me_);
    ju.set_time("sharedWithMeTime", shared_with_me_time_);
    ju.set_object("sharingUser", sharing_user_);
    ju.set_object_vector("owners", owners_);
    ju.set_string("teamDriveId", team_drive_id_);
    ju.set_string("driveId", drive_id_);
    ju.set_object("lastModifyingUser", last_modifying_user_);
    ju.set_bool("shared", shared_);
    ju.set_bool("ownedByMe", owned_by_me_);
    ju.set_object("capabilities", capabilities_);
    ju.set_bool("copyRequiresWriterPermission", copy_requires_writer_permission_);
    ju.set_bool("writersCanShare", writers_can_share_);
    ju.set_object_vector("permissions", permissions_);
    ju.set_string_vector("permissionIds", permission_ids_);
    ju.set_bool("hasAugmentedPermissions", has_augmented_permissions_);
    ju.set_string("folderColorRgb", folder_color_rgb_);
    ju.set_string("originalFileName", original_file_name_);
    ju.set_string("fullFileExtension", full_file_extension_);
    ju.set_string("fileExtension", file_extension_);
    ju.set_string("md5Checksum", md5_checksum_);
    ju.set_number_from_string("size", size_);
    ju.set_number_from_string("quotaBytesUsed", quota_bytes_used_);
    ju.set_string("headRevisionId", head_revision_id_);
    ju.set_object("contentHints", content_hints_);
    ju.set_object("imageMediaMetadata", image_media_metadata_);
    ju.set_object("videoMediaMetadata", video_media_metadata_);
    ju.set_bool("isAppAuthorized", is_app_authorized_);
    ju.set_map("exportLinks", export_links_);
    ju.set_object("shortcutDetails", shortcut_details_);
    ju.set_object_vector("contentRestrictions", content_restrictions_);
}

void file::to_json(cJSON& json)
{
    cjson::util ju(json);
    ju.add_map("appProperties", app_properties_);
    ju.add_bool("copyRequiresWriterPermission", copy_requires_writer_permission_);
    ju.add_time("createdTime", created_time_);
    ju.add_string("description", description_);
    ju.add_string("folderColorRgb", folder_color_rgb_);
    ju.add_string("id", id_);
    ju.add_string("name", name_);
    ju.add_string("mimeType", mime_type_);
    ju.add_time("modifiedTime", modified_time_);
    ju.add_string("originalFileName", original_file_name_);
    ju.add_string_vector("parents", parents_);
    ju.add_map("properties", properties_);
    ju.add_object("contentHints", content_hints_);
    ju.add_object_vector("contentRestrictions", content_restrictions_);
    ju.add_bool("starred", starred_);
    ju.add_time("viewedByMeTime", viewed_by_me_time_);
    ju.add_bool("writersCanShare", writers_can_share_);
}

}