#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

using namespace std::chrono_literals;

class permissions_update : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("permissions_update");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(permissions_update, one)
{
    espadin::permission perm;
    perm.role("reader")
        .type("user")
        .email_address("will@chucho-log.org");
    auto perms = drive_.permissions(file_id_);
    auto creply = perms->create(std::move(perm))->run();
    ASSERT_TRUE(creply);
    ASSERT_TRUE(creply->id());
    espadin::permission perm2;
    perm2.role("writer");
    auto result = perms->update(*creply->id(), std::move(perm2))->run();
    ASSERT_TRUE(result);
    EXPECT_TRUE(result->kind());
    EXPECT_TRUE(result->id());
    EXPECT_TRUE(result->type());
    ASSERT_TRUE(result->role());
    EXPECT_STREQ("writer", result->role()->c_str());
}