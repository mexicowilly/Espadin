#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class permissions_list : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("permissions_list");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(permissions_list, all)
{
    espadin::permission perm;
    perm.role("reader")
        .type("user")
        .email_address("will@chucho-log.org");
    auto perms = drive_.permissions(file_id_);
    auto creply = perms->create(std::move(perm))->run();
    ASSERT_TRUE(creply);
    ASSERT_TRUE(creply->id());
    auto lst = perms->list();
    lst->page_size(1)
        .fields("kind,nextPageToken,permissions/id");
    auto result = lst->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#permissionList", result->kind()->c_str());
    ASSERT_TRUE(result->next_page_token());
    ASSERT_TRUE(result->permissions());
    EXPECT_EQ(1, result->permissions()->size());
    auto id1 = *result->permissions()->at(0).id();
    lst->page_token(*result->next_page_token());
    result = lst->run();
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#permissionList", result->kind()->c_str());
    EXPECT_FALSE(result->next_page_token());
    ASSERT_TRUE(result->permissions());
    EXPECT_EQ(1, result->permissions()->size());
    auto id2 = *result->permissions()->at(0).id();
    EXPECT_STRNE(id1.c_str(), id2.c_str());
}