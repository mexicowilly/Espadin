#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class replies_update : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("replies_update");
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

TEST_F(replies_update, one)
{
    auto rep = drive_.replies(file_id_, comment_id_);
    ASSERT_TRUE(rep);
    espadin::reply data;
    data.content("This comment sucks");
    auto result = rep->create(std::move(data), "id")->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->id());
    result = rep->update(*result->id(), "This comment is good", "content")->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->content());
    EXPECT_STREQ("This comment is good", result->content()->c_str());
}