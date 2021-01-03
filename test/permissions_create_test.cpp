#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class permissions_create : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("permissions_create");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(permissions_create, reader)
{
    espadin::permission perm;
    perm.role("reader")
        .type("user")
        .email_address("will@chucho-log.org");
    auto perms = drive_.permissions(file_id_);
    ASSERT_TRUE(perms);
    auto result = perms->create(std::move(perm))->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#permission", result->kind()->c_str());
    EXPECT_TRUE(result->id());
    ASSERT_TRUE(result->type());
    EXPECT_STREQ("user", result->type()->c_str());
    ASSERT_TRUE(result->role());
    EXPECT_STREQ("reader", result->role()->c_str());
}