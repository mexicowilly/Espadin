#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class replies_create : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("replies_create")
                .mime_type("application/vnd.google-apps.document");
        auto reply = drive_.files()->create(std::move(metadata))->run();
        ASSERT_TRUE(reply);
        ASSERT_TRUE(reply->id());
        file_id_ = *reply->id();
        auto creply = drive_.comments(file_id_)->create("This is a comment", "id")->run();
        ASSERT_TRUE(creply);
        ASSERT_TRUE(creply->id());
        comment_id_ = *creply->id();
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
    std::string comment_id_;
};

}

TEST_F(replies_create, one)
{
    auto rep = drive_.replies(file_id_, comment_id_);
    ASSERT_TRUE(rep);
    espadin::reply data;
    data.content("This comment sucks");
    auto result = rep->create(std::move(data), "*")->run();
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#reply", result->kind()->c_str());
    EXPECT_TRUE(result->id());
    EXPECT_TRUE(result->created_time());
    EXPECT_TRUE(result->modified_time());
    EXPECT_TRUE(result->author());
    EXPECT_TRUE(result->html_content());
    EXPECT_TRUE(result->content());
    ASSERT_TRUE(result->deleted());
    EXPECT_FALSE(result->deleted().value());
}

TEST_F(replies_create, resolve)
{
    auto rep = drive_.replies(file_id_, comment_id_);
    ASSERT_TRUE(rep);
    espadin::reply data;
    data.action("resolve");
    auto result = rep->create(std::move(data), "*")->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->kind());
    EXPECT_STREQ("drive#reply", result->kind()->c_str());
    EXPECT_TRUE(result->id());
    EXPECT_TRUE(result->created_time());
    EXPECT_TRUE(result->modified_time());
    EXPECT_TRUE(result->author());
    EXPECT_FALSE(result->html_content());
    EXPECT_FALSE(result->content());
    ASSERT_TRUE(result->deleted());
    EXPECT_FALSE(result->deleted().value());
    auto cmnt = drive_.comments(file_id_)->get(comment_id_, "resolved")->run();
    ASSERT_TRUE(cmnt);
    ASSERT_TRUE(cmnt->resolved());
    EXPECT_TRUE(cmnt->resolved().value());
}