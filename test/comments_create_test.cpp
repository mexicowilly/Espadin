#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class comments_create : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("comments_create");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(comments_create, add_one)
{
    auto cmts = drive_.comments(file_id_);
    auto reply = cmts->create("This is a comment", "*")->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->created_time());
    EXPECT_TRUE(reply->modified_time());
    auto author = reply->author();
    ASSERT_TRUE(author);
    EXPECT_TRUE(author->kind());
    EXPECT_TRUE(author->display_name());
    EXPECT_TRUE(author->photo_link());
    EXPECT_TRUE(author->me());
    EXPECT_TRUE(reply->html_content());
    EXPECT_TRUE(reply->content());
    EXPECT_TRUE(reply->deleted());
    ASSERT_TRUE(reply->replies());
    EXPECT_TRUE(reply->replies()->empty());
}