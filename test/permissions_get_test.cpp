#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class permissions_get : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("permissions_get");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(permissions_get, all)
{
    espadin::permission perm;
    perm.role("reader")
        .type("user")
        .email_address("will@chucho-log.org");
    auto perms = drive_.permissions(file_id_);
    auto creply = perms->create(std::move(perm))->run();
    ASSERT_TRUE(creply);
    ASSERT_TRUE(creply->id());
    auto result = perms->get(*creply->id())->fields("*").run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#permission", result->kind()->c_str());
    ASSERT_TRUE(result->id());
    EXPECT_STREQ(creply->id()->c_str(), result->id()->c_str());
    ASSERT_TRUE(result->type());
    EXPECT_STREQ("user", result->type()->c_str());
    ASSERT_TRUE(result->email_address());
    EXPECT_STREQ("will@chucho-log.org", result->email_address()->c_str());
    ASSERT_TRUE(result->role());
    EXPECT_STREQ("reader", result->role()->c_str());
    EXPECT_TRUE(result->display_name());
    ASSERT_TRUE(result->deleted());
    EXPECT_FALSE(result->deleted().value());
}