#include <espadin/capabilities.hpp>
#include "cjson_util.hpp"

namespace espadin
{

capabilities::capabilities(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_bool("canAddChildren", can_add_children_);
    ju.set_bool("canAddFolderFromAnotherDrive", can_add_folder_from_another_drive_);
    ju.set_bool("canAddMyDriveParent", can_add_my_drive_parent_);
    ju.set_bool("canChangeCopyRequiresWriterPermission", can_change_copy_requires_writer_permission_);
    ju.set_bool("canChangeViewersCanCopyContent", can_change_viewers_can_copy_content_);
    ju.set_bool("canComment", can_comment_);
    ju.set_bool("canCopy", can_copy_);
    ju.set_bool("canDelete", can_delete_);
    ju.set_bool("canDeleteChildren", can_delete_children_);
    ju.set_bool("canDownload", can_download_);
    ju.set_bool("canEdit", can_edit_);
    ju.set_bool("canListChildren", can_list_children_);
    ju.set_bool("canModifyContent", can_modify_content_);
    ju.set_bool("canModifyContentRestriction", can_modify_content_restriction_);
    ju.set_bool("canMoveChildrenOutOfTeamDrive", can_move_children_out_of_team_drive_);
    ju.set_bool("canMoveChildrenOutOfDrive", can_move_children_out_of_drive_);
    ju.set_bool("canMoveChildrenWithinTeamDrive", can_move_children_within_team_drive_);
    ju.set_bool("canMoveChildrenWithinDrive", can_move_children_within_drive_);
    ju.set_bool("canMoveItemIntoTeamDrive", can_move_item_into_team_drive_);
    ju.set_bool("canMoveItemOutOfTeamDrive", can_move_item_out_of_team_drive_);
    ju.set_bool("canMoveItemOutOfDrive", can_move_item_out_of_drive_);
    ju.set_bool("canMoveItemWithinTeamDrive", can_move_item_within_team_drive_);
    ju.set_bool("canMoveItemWithinDrive", can_move_item_within_drive_);
    ju.set_bool("canMoveTeamDriveItem", can_move_team_drive_item_);
    ju.set_bool("canReadRevisions", can_read_revisions_);
    ju.set_bool("canReadTeamDrive", can_read_team_drive_);
    ju.set_bool("canReadDrive", can_read_drive_);
    ju.set_bool("canRemoveChildren", can_remove_children_);
    ju.set_bool("canRemoveMyDriveParent", can_remove_my_drive_parent_);
    ju.set_bool("canRename", can_rename_);
    ju.set_bool("canShare", can_share_);
    ju.set_bool("canTrash", can_trash_);
    ju.set_bool("canTrashChildren", can_trash_children_);
    ju.set_bool("canUntrash", can_untrash_);
}

}