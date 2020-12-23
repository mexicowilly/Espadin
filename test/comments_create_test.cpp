#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class comments_create : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("comments_create")
                .mime_type("application/vnd.google-apps.document");
        auto reply = drive_.files()->create(std::move(metadata))->run();
        ASSERT_TRUE(reply->id());
        file_id_ = *reply->id();
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
    auto cmts = drive_.comments();
    auto reply = cmts->create(file_id_, "This is a comment", "*")->run();
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