#include <espadin/capabilities.hpp>
#include "cJSON.h"
#include <stdexcept>

namespace espadin
{

capabilities::capabilities(const cJSON& json)
{
    set_value(json, "canAddChildren", CAN_ADD_CHILDREN);
    set_value(json, "canAddFolderFromAnotherDrive", CAN_ADD_FOLDER_FROM_ANOTHER_DRIVE);
    set_value(json, "canAddMyDriveParent", CAN_ADD_MY_DRIVE_PARENT);
    set_value(json, "canChangeCopyRequiresWriterPermission", CAN_CHANGE_COPY_REQUIRES_WRITER_PERMISSION);
    set_value(json, "canChangeViewerCanCopyContent", CAN_CHANGE_VIEWER_CAN_COPY_CONTENT);
    set_value(json, "canComment", CAN_COMMENT);
    set_value(json, "canCopy", CAN_COPY);
    set_value(json, "canDelete", CAN_DELETE);
    set_value(json, "canDeleteChildren", CAN_DELETE_CHILDREN);
    set_value(json, "canDownload", CAN_DOWNLOAD);
    set_value(json, "canEdit", CAN_EDIT);
    set_value(json, "canListChildren", CAN_LIST_CHILDREN);
    set_value(json, "canModifyContent", CAN_MODIFY_CONTENT);
    set_value(json, "canModifyContentRestriction", CAN_MODIFY_CONTENT_RESTRICTION);
    set_value(json, "canMoveChildrenOutOfTeamDrive", CAN_MOVE_CHILDREN_OUT_OF_TEAM_DRIVE);
    set_value(json, "canMoveChildrenOutOfDrive", CAN_MOVE_CHILDREN_OUT_OF_DRIVE);
    set_value(json, "canMoveChildrenWithinTeamDrive", CAN_MOVE_CHILDREN_WITHIN_TEAM_DRIVE);
    set_value(json, "canMoveChildrenWithinDrive", CAN_MOVE_CHILDREN_WITHIN_DRIVE);
    set_value(json, "canMoveItemIntoTeamDrive", CAN_MOVE_ITEM_INTO_TEAM_DRIVE);
    set_value(json, "canMoveItemOutOfTeamDrive", CAN_MOVE_ITEM_OUT_OF_TEAM_DRIVE);
    set_value(json, "canMoveItemOutOfDrive", CAN_MOVE_ITEM_OUT_OF_DRIVE);
    set_value(json, "canMoveItemWithinTeamDrive", CAN_MOVE_ITEM_WITHIN_TEAM_DRIVE);
    set_value(json, "canMoveItemWithinDrive", CAN_MOVE_ITEM_WITHIN_DRIVE);
    set_value(json, "canMoveTeamDriveItem", CAN_MOVE_TEAM_DRIVE_ITEM);
    set_value(json, "canReadRevisions", CAN_READ_REVISIONS);
    set_value(json, "canReadTeamDrive", CAN_READ_TEAM_DRIVE);
    set_value(json, "canReadDrive", CAN_READ_DRIVE);
    set_value(json, "canRemoveChildren", CAN_REMOVE_CHILDREN);
    set_value(json, "canRemoveMyDriveParent", CAN_REMOVE_MY_DRIVE_PARENT);
    set_value(json, "canRename", CAN_RENAME);
    set_value(json, "canShare", CAN_SHARE);
    set_value(json, "canTrash", CAN_TRASH);
    set_value(json, "canTrashChildren", CAN_TRASH_CHILDREN);
    set_value(json, "canUntrash", CAN_UNTRASH);
}

void capabilities::set_value(const cJSON& json, const char* const name, item it)
{
    auto bool_obj = cJSON_GetObjectItem(&json, name);
    if (bool_obj != nullptr)
    {
        if (cJSON_IsBool(bool_obj))
            caps_.set(it, bool_obj->type == cJSON_True);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a bool");
    }
}

}