#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class replies_list : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("replies_list")
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

TEST_F(replies_list, pages)
{
    auto rpls = drive_.replies(file_id_, comment_id_);
    std::set<std::string> created;
    for (int i = 0; i < 5; i++)
    {
        espadin::reply data;
        data.content(std::to_string(i));
        auto reply = rpls->create(std::move(data), "id")->run();
        ASSERT_TRUE(reply);
        ASSERT_TRUE(reply->id());
        created.insert(*reply->id());
    }
    auto lst = rpls->list("nextPageToken, replies/id");
    lst->page_size(3);
    auto result = lst->run();
    ASSERT_TRUE(result);
    ASSERT_TRUE(result->next_page_token());
    ASSERT_TRUE(result->replies());
    EXPECT_EQ(3, result->replies()->size());
    std::set<std::string> found;
    for (const auto& rep : *result->replies())
    {
        ASSERT_TRUE(rep.id());
        found.insert(*rep.id());
    }
    lst->page_token(*result->next_page_token());
    result = lst->run();
    ASSERT_TRUE(result);
    EXPECT_FALSE(result->next_page_token());
    ASSERT_TRUE(result->replies());
    EXPECT_EQ(2, result->replies()->size());
    for (const auto& rep : *result->replies())
    {
        ASSERT_TRUE(rep.id());
        found.insert(*rep.id());
    }
    EXPECT_EQ(created, found);
}