#if !defined(ESPADING_CAPABILITIES_HPP__)
#define ESPADING_CAPABILITIES_HPP__

#include <espadin/export.hpp>
#include <bitset>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT capabilities
{
public:
    enum item
    {
        CAN_ADD_CHILDREN,
        CAN_ADD_FOLDER_FROM_ANOTHER_DRIVE,
        CAN_ADD_MY_DRIVE_PARENT,
        CAN_CHANGE_COPY_REQUIRES_WRITER_PERMISSION,
        CAN_CHANGE_VIEWER_CAN_COPY_CONTENT,
        CAN_COMMENT,
        CAN_COPY,
        CAN_DELETE,
        CAN_DELETE_CHILDREN,
        CAN_DOWNLOAD,
        CAN_EDIT,
        CAN_LIST_CHILDREN,
        CAN_MODIFY_CONTENT,
        CAN_MODIFY_CONTENT_RESTRICTION,
        CAN_MOVE_CHILDREN_OUT_OF_TEAM_DRIVE,
        CAN_MOVE_CHILDREN_OUT_OF_DRIVE,
        CAN_MOVE_CHILDREN_WITHIN_TEAM_DRIVE,
        CAN_MOVE_CHILDREN_WITHIN_DRIVE,
        CAN_MOVE_ITEM_INTO_TEAM_DRIVE,
        CAN_MOVE_ITEM_OUT_OF_TEAM_DRIVE,
        CAN_MOVE_ITEM_OUT_OF_DRIVE,
        CAN_MOVE_ITEM_WITHIN_TEAM_DRIVE,
        CAN_MOVE_ITEM_WITHIN_DRIVE,
        CAN_MOVE_TEAM_DRIVE_ITEM,
        CAN_READ_REVISIONS,
        CAN_READ_TEAM_DRIVE,
        CAN_READ_DRIVE,
        CAN_REMOVE_CHILDREN,
        CAN_REMOVE_MY_DRIVE_PARENT,
        CAN_RENAME,
        CAN_SHARE,
        CAN_TRASH,
        CAN_TRASH_CHILDREN,
        CAN_UNTRASH,
        ITEM_COUNT
    };

    capabilities(const cJSON& json);

    bool get(item it) const;

private:
    void set_value(const cJSON& json, const char* const name, item it);

    std::bitset<ITEM_COUNT> caps_;
};

inline bool capabilities::get(item it) const
{
    return caps_.test(it);
}

}

#endif