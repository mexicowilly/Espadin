#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class permissions_delete : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("permissions_delete");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(permissions_delete, do_one)
{
    espadin::permission perm;
    perm.role("reader")
        .type("user")
        .email_address("will@chucho-log.org");
    auto perms = drive_.permissions(file_id_);
    auto result = perms->create(std::move(perm))->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->id());
    perms->del(*result->id())->run();
    EXPECT_THROW(perms->get(*result->id())->run(), espadin::drive_exception);
}
