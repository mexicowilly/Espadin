#include <gtest/gtest.h>
#include "base_test.hpp"
#include <iostream>
#include <fstream>
#include <iterator>

namespace
{

class files_get : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        files_ = drive_.files();
    }

    bool files_are_equal(const std::filesystem::path& partial, const std::filesystem::path& full)
    {
        bool result = false;
        auto one = std::filesystem::temp_directory_path() / partial;
        if (std::filesystem::file_size(one) == std::filesystem::file_size(full))
        {
            std::ifstream one_in(one);
            std::ifstream two_in(full);
            result = std::equal(std::istream_iterator<char>(one_in),
                                std::istream_iterator<char>(),
                                std::istream_iterator<char>(two_in));
        }
        return result;
    }

    std::string create_file(const std::filesystem::path& name)
    {
        auto full = std::filesystem::temp_directory_path() / name;
        std::ofstream stream(full);
        for (int i = 0; i < 2 * 1024 * 1024; i++)
            stream << static_cast<char>((i % 32) + 32);
        stream.close();
        espadin::file meta;
        meta.name(name.string())
            .parents({parent_id});
        auto reply = files_->create(std::move(meta), full)->run();
        EXPECT_TRUE(reply);
        EXPECT_TRUE(reply->id());
        return *reply->id();
    }

    void delete_file(const std::filesystem::path& name)
    {
        std::filesystem::remove(std::filesystem::temp_directory_path() / name);
    }

    std::unique_ptr<espadin::files_group> files_;
};

}

TEST_F(files_get, meta)
{
    std::filesystem::path fname("files_get_meta.txt");
    auto id = create_file(fname);
    auto get = files_->get(id);
    get->fields("*");
    auto reply = get->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->kind());
    EXPECT_STREQ("drive#file", reply->kind()->c_str());
    ASSERT_TRUE(reply->id());
    EXPECT_STREQ(id.c_str(), reply->id()->c_str());
    ASSERT_TRUE(reply->name());
    EXPECT_STREQ(fname.filename().c_str(), reply->name()->c_str());
    ASSERT_TRUE(reply->mime_type());
    EXPECT_STREQ("text/plain", reply->mime_type()->c_str());
    ASSERT_TRUE(reply->starred());
    EXPECT_FALSE(reply->starred().value());
    ASSERT_TRUE(reply->trashed());
    EXPECT_FALSE(reply->trashed().value());
    ASSERT_TRUE(reply->explicitly_trashed());
    EXPECT_FALSE(reply->explicitly_trashed().value());
    ASSERT_TRUE(reply->parents());
    ASSERT_EQ(1, reply->parents()->size());
    EXPECT_STREQ(parent_id.c_str(), reply->parents()->at(0).c_str());
    ASSERT_TRUE(reply->spaces());
    ASSERT_EQ(1, reply->spaces()->size());
    EXPECT_STREQ("drive", reply->spaces()->at(0).c_str());
    EXPECT_TRUE(reply->version());
    EXPECT_TRUE(reply->web_content_link());
    EXPECT_TRUE(reply->web_view_link());
    EXPECT_TRUE(reply->icon_link());
    ASSERT_TRUE(reply->has_thumbnail());
    EXPECT_FALSE(reply->has_thumbnail().value());
    EXPECT_TRUE(reply->thumbnail_version());
    ASSERT_TRUE(reply->viewed_by_me());
    EXPECT_FALSE(reply->viewed_by_me().value());
    EXPECT_TRUE(reply->created_time());
    EXPECT_TRUE(reply->modified_time());
    EXPECT_TRUE(reply->modified_by_me_time());
    ASSERT_TRUE(reply->modified_by_me());
    EXPECT_TRUE(reply->modified_by_me().value());
    ASSERT_TRUE(reply->owners());
    ASSERT_EQ(1, reply->owners()->size());
    const auto& owner = reply->owners()->at(0);
    ASSERT_TRUE(owner.kind());
    EXPECT_STREQ("drive#user", owner.kind()->c_str());
    EXPECT_TRUE(owner.display_name());
    EXPECT_TRUE(owner.photo_link());
    ASSERT_TRUE(owner.me());
    EXPECT_TRUE(owner.me().value());
    EXPECT_TRUE(owner.permission_id());
    EXPECT_TRUE(owner.email_address());
    ASSERT_TRUE(reply->last_modifying_user());
    const auto& mod_user = *reply->last_modifying_user();
    ASSERT_TRUE(mod_user.kind());
    EXPECT_STREQ("drive#user", mod_user.kind()->c_str());
    EXPECT_TRUE(mod_user.display_name());
    EXPECT_TRUE(mod_user.photo_link());
    ASSERT_TRUE(mod_user.me());
    EXPECT_TRUE(mod_user.me().value());
    EXPECT_TRUE(mod_user.permission_id());
    EXPECT_TRUE(mod_user.email_address());
    ASSERT_TRUE(reply->shared());
    EXPECT_FALSE(reply->shared().value());
    ASSERT_TRUE(reply->owned_by_me());
    EXPECT_TRUE(reply->owned_by_me().value());
    ASSERT_TRUE(reply->get_capabilities());
    const auto& caps = *reply->get_capabilities();
    ASSERT_TRUE(caps.can_add_children());
    EXPECT_FALSE(caps.can_add_children().value());
    EXPECT_TRUE(caps.can_add_my_drive_parent());
    EXPECT_TRUE(caps.can_change_copy_requires_writer_permission());
    EXPECT_TRUE(caps.can_change_viewers_can_copy_content());
    EXPECT_TRUE(caps.can_copy());
    EXPECT_TRUE(caps.can_delete());
    EXPECT_TRUE(caps.can_download());
    EXPECT_TRUE(caps.can_edit());
    EXPECT_TRUE(caps.can_list_children());
    EXPECT_TRUE(caps.can_modify_content());
    EXPECT_TRUE(caps.can_move_children_within_drive());
    EXPECT_TRUE(caps.can_move_item_into_team_drive());
    EXPECT_TRUE(caps.can_move_item_out_of_drive());
    EXPECT_TRUE(caps.can_move_item_within_drive());
    EXPECT_TRUE(caps.can_read_revisions());
    EXPECT_TRUE(caps.can_remove_children());
    EXPECT_TRUE(caps.can_remove_my_drive_parent());
    EXPECT_TRUE(caps.can_rename());
    EXPECT_TRUE(caps.can_share());
    EXPECT_TRUE(caps.can_trash());
    EXPECT_TRUE(caps.can_untrash());
    EXPECT_TRUE(reply->viewers_can_copy_content());
    EXPECT_TRUE(reply->copy_requires_writer_permission());
    EXPECT_TRUE(reply->writers_can_share());
    ASSERT_TRUE(reply->permissions());
    // The individual permissions fields are checked in the permissions tests
    EXPECT_EQ(1, reply->permissions()->size());
    ASSERT_TRUE(reply->permission_ids());
    EXPECT_EQ(1, reply->permission_ids()->size());
    ASSERT_TRUE(reply->original_file_name());
    EXPECT_STREQ(fname.c_str(), reply->original_file_name()->c_str());
    EXPECT_TRUE(reply->full_file_extension());
    EXPECT_TRUE(reply->file_extension());
    ASSERT_TRUE(reply->md5_checksum());
    EXPECT_TRUE(reply->size());
    EXPECT_TRUE(reply->quota_bytes_used());
    EXPECT_TRUE(reply->head_revision_id());
    EXPECT_TRUE(reply->is_app_authorized());
    delete_file(fname);
    trash(id);
}

TEST_F(files_get, contents)
{
    std::filesystem::path fname("files_get_contents.txt");
    auto id = create_file(fname);
    std::filesystem::path dl_name(std::filesystem::temp_directory_path() / "files_get_contents_to_compare.txt");
    std::ofstream out(dl_name);
    auto get = files_->get(id, out);
    auto reply = get->run();
    out.close();
    EXPECT_FALSE(reply);
    EXPECT_TRUE(files_are_equal(fname, dl_name));
    std::filesystem::remove(dl_name);
    delete_file(fname);
    trash(id);
}