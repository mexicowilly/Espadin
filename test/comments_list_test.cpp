#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class comments_list : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("comments_list");
        auto cmts = drive_.comments(file_id_);
        for (int i = 0; i < 5; i++)
        {
            auto r2 = cmts->create(std::to_string(i), "id")->run();
            ASSERT_TRUE(r2);
            ASSERT_TRUE(r2->id());
        }
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(comments_list, pages)
{
    auto lst = drive_.comments(file_id_)->list("*");
    auto reply = lst->page_size(3).run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->next_page_token());
    ASSERT_TRUE(reply->comments());
    EXPECT_EQ(3, reply->comments()->size());
    reply = lst->page_token(*reply->next_page_token()).run();
    ASSERT_TRUE(reply);
    ASSERT_FALSE(reply->next_page_token());
    ASSERT_TRUE(reply->comments());
    EXPECT_EQ(2, reply->comments()->size());
}

