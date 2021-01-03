#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class comments_delete : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("comments_delete");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(comments_delete, delete_one)
{
    auto cmts = drive_.comments(file_id_);
    auto reply = cmts->create("This is a comment", "id")->run();
    ASSERT_TRUE(reply->id());
    cmts->del(*reply->id())->run();
    EXPECT_THROW(cmts->get(*reply->id(), "id")->run(), espadin::drive_exception);
}