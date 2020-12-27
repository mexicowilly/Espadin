#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class comments_get : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("comments_get")
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

TEST_F(comments_get, get_one)
{
    auto cmts = drive_.comments(file_id_);
    auto reply = cmts->create("This is a comment", "id")->run();
    ASSERT_TRUE(reply->id());
    auto reply2 = cmts->get(*reply->id(), "*")->run();
    EXPECT_TRUE(reply2->kind());
    EXPECT_TRUE(reply2->id());
    EXPECT_TRUE(reply2->created_time());
    EXPECT_TRUE(reply2->modified_time());
    auto author = reply2->author();
    ASSERT_TRUE(author);
    EXPECT_TRUE(author->kind());
    EXPECT_TRUE(author->display_name());
    EXPECT_TRUE(author->photo_link());
    EXPECT_TRUE(author->me());
    EXPECT_TRUE(reply2->html_content());
    EXPECT_TRUE(reply2->content());
    EXPECT_TRUE(reply2->deleted());
    ASSERT_TRUE(reply2->replies());
    EXPECT_TRUE(reply2->replies()->empty());
}
