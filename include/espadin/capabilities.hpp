#if !defined(ESPADING_CAPABILITIES_HPP_)
#define ESPADING_CAPABILITIES_HPP_

#include <espadin/export.hpp>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT capabilities
{
public:
    capabilities(const cJSON& json);

    const std::optional<bool>& can_add_children() const;
    const std::optional<bool>& can_add_folder_from_another_drive() const;
    const std::optional<bool>& can_add_my_drive_parent() const;
    const std::optional<bool>& can_change_copy_requires_writer_permission() const;
    const std::optional<bool>& can_change_viewers_can_copy_content() const;
    const std::optional<bool>& can_comment() const;
    const std::optional<bool>& can_copy() const;
    const std::optional<bool>& can_delete() const;
    const std::optional<bool>& can_delete_children() const;
    const std::optional<bool>& can_download() const;
    const std::optional<bool>& can_edit() const;
    const std::optional<bool>& can_list_children() const;
    const std::optional<bool>& can_modify_content() const;
    const std::optional<bool>& can_modify_content_restriction() const;
    const std::optional<bool>& can_move_children_out_of_team_drive() const;
    const std::optional<bool>& can_move_children_out_of_drive() const;
    const std::optional<bool>& can_move_children_within_team_drive() const;
    const std::optional<bool>& can_move_children_within_drive() const;
    const std::optional<bool>& can_move_item_into_team_drive() const;
    const std::optional<bool>& can_move_item_out_of_team_drive() const;
    const std::optional<bool>& can_move_item_out_of_drive() const;
    const std::optional<bool>& can_move_item_within_team_drive() const;
    const std::optional<bool>& can_move_item_within_drive() const;
    const std::optional<bool>& can_move_team_drive_item() const;
    const std::optional<bool>& can_read_revisions() const;
    const std::optional<bool>& can_read_team_drive() const;
    const std::optional<bool>& can_read_drive() const;
    const std::optional<bool>& can_remove_children() const;
    const std::optional<bool>& can_remove_my_drive_parent() const;
    const std::optional<bool>& can_rename() const;
    const std::optional<bool>& can_share() const;
    const std::optional<bool>& can_trash() const;
    const std::optional<bool>& can_trash_children() const;
    const std::optional<bool>& can_untrash() const;

private:
    std::optional<bool> can_add_children_;
    std::optional<bool> can_add_folder_from_another_drive_;
    std::optional<bool> can_add_my_drive_parent_;
    std::optional<bool> can_change_copy_requires_writer_permission_;
    std::optional<bool> can_change_viewers_can_copy_content_;
    std::optional<bool> can_comment_;
    std::optional<bool> can_copy_;
    std::optional<bool> can_delete_;
    std::optional<bool> can_delete_children_;
    std::optional<bool> can_download_;
    std::optional<bool> can_edit_;
    std::optional<bool> can_list_children_;
    std::optional<bool> can_modify_content_;
    std::optional<bool> can_modify_content_restriction_;
    std::optional<bool> can_move_children_out_of_team_drive_;
    std::optional<bool> can_move_children_out_of_drive_;
    std::optional<bool> can_move_children_within_team_drive_;
    std::optional<bool> can_move_children_within_drive_;
    std::optional<bool> can_move_item_into_team_drive_;
    std::optional<bool> can_move_item_out_of_team_drive_;
    std::optional<bool> can_move_item_out_of_drive_;
    std::optional<bool> can_move_item_within_team_drive_;
    std::optional<bool> can_move_item_within_drive_;
    std::optional<bool> can_move_team_drive_item_;
    std::optional<bool> can_read_revisions_;
    std::optional<bool> can_read_team_drive_;
    std::optional<bool> can_read_drive_;
    std::optional<bool> can_remove_children_;
    std::optional<bool> can_remove_my_drive_parent_;
    std::optional<bool> can_rename_;
    std::optional<bool> can_share_;
    std::optional<bool> can_trash_;
    std::optional<bool> can_trash_children_;
    std::optional<bool> can_untrash_;
};

inline const std::optional<bool>& capabilities::can_add_children() const
{
    return can_add_children_;
}

inline const std::optional<bool>& capabilities::can_add_folder_from_another_drive() const
{
    return can_add_folder_from_another_drive_;
}

inline const std::optional<bool>& capabilities::can_add_my_drive_parent() const
{
    return can_add_my_drive_parent_;
}

inline const std::optional<bool>& capabilities::can_change_copy_requires_writer_permission() const
{
    return can_change_copy_requires_writer_permission_;
}

inline const std::optional<bool>& capabilities::can_change_viewers_can_copy_content() const
{
    return can_change_viewers_can_copy_content_;
}

inline const std::optional<bool>& capabilities::can_comment() const
{
    return can_comment_;
}

inline const std::optional<bool>& capabilities::can_copy() const
{
    return can_copy_;
}

inline const std::optional<bool>& capabilities::can_delete() const
{
    return can_delete_;
}

inline const std::optional<bool>& capabilities::can_delete_children() const
{
    return can_delete_children_;
}

inline const std::optional<bool>& capabilities::can_download() const
{
    return can_download_;
}

inline const std::optional<bool>& capabilities::can_edit() const
{
    return can_edit_;
}

inline const std::optional<bool>& capabilities::can_list_children() const
{
    return can_list_children_;
}

inline const std::optional<bool>& capabilities::can_modify_content() const
{
    return can_modify_content_;
}

inline const std::optional<bool>& capabilities::can_modify_content_restriction() const
{
    return can_modify_content_restriction_;
}

inline const std::optional<bool>& capabilities::can_move_children_out_of_team_drive() const
{
    return can_move_children_out_of_team_drive_;
}

inline const std::optional<bool>& capabilities::can_move_children_out_of_drive() const
{
    return can_move_children_out_of_drive_;
}

inline const std::optional<bool>& capabilities::can_move_children_within_team_drive() const
{
    return can_move_children_within_team_drive_;
}

inline const std::optional<bool>& capabilities::can_move_children_within_drive() const
{
    return can_move_children_within_drive_;
}

inline const std::optional<bool>& capabilities::can_move_item_into_team_drive() const
{
    return can_move_item_into_team_drive_;
}

inline const std::optional<bool>& capabilities::can_move_item_out_of_team_drive() const
{
    return can_move_item_out_of_team_drive_;
}

inline const std::optional<bool>& capabilities::can_move_item_out_of_drive() const
{
    return can_move_item_out_of_drive_;
}

inline const std::optional<bool>& capabilities::can_move_item_within_team_drive() const
{
    return can_move_item_within_team_drive_;
}

inline const std::optional<bool>& capabilities::can_move_item_within_drive() const
{
    return can_move_item_within_drive_;
}

inline const std::optional<bool>& capabilities::can_move_team_drive_item() const
{
    return can_move_team_drive_item_;
}

inline const std::optional<bool>& capabilities::can_read_revisions() const
{
    return can_read_revisions_;
}

inline const std::optional<bool>& capabilities::can_read_team_drive() const
{
    return can_read_team_drive_;
}

inline const std::optional<bool>& capabilities::can_read_drive() const
{
    return can_read_drive_;
}

inline const std::optional<bool>& capabilities::can_remove_children() const
{
    return can_remove_children_;
}

inline const std::optional<bool>& capabilities::can_remove_my_drive_parent() const
{
    return can_remove_my_drive_parent_;
}

inline const std::optional<bool>& capabilities::can_rename() const
{
    return can_rename_;
}

inline const std::optional<bool>& capabilities::can_share() const
{
    return can_share_;
}

inline const std::optional<bool>& capabilities::can_trash() const
{
    return can_trash_;
}

inline const std::optional<bool>& capabilities::can_trash_children() const
{
    return can_trash_children_;
}

inline const std::optional<bool>& capabilities::can_untrash() const
{
    return can_untrash_;
}

}

#endif