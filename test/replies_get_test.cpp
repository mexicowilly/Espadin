#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class replies_get : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("replies_get");
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

TEST_F(replies_get, get_one)
{
    auto rep = drive_.replies(file_id_, comment_id_);
    espadin::reply data;
    data.content("This comment sucks");
    auto crep = rep->create(std::move(data), "id")->run();
    ASSERT_TRUE(crep);
    ASSERT_TRUE(crep->id());
    auto grep = rep->get(*crep->id(), "*")->run();
    ASSERT_TRUE(grep->kind());
    EXPECT_STREQ("drive#reply", grep->kind()->c_str());
    EXPECT_TRUE(grep->id());
    EXPECT_TRUE(grep->created_time());
    EXPECT_TRUE(grep->modified_time());
    EXPECT_TRUE(grep->author());
    EXPECT_TRUE(grep->html_content());
    EXPECT_TRUE(grep->content());
    ASSERT_TRUE(grep->deleted());
    EXPECT_FALSE(grep->deleted().value());
    auto cmt = drive_.comments(file_id_)->get(comment_id_, "replies")->run();
    ASSERT_TRUE(cmt);
    ASSERT_TRUE(cmt->replies());
    EXPECT_EQ(1, cmt->replies()->size());
}