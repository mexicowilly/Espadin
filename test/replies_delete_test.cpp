#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class replies_delete : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("replies_get")
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

TEST_F(replies_delete, delete_one)
{
    auto rep = drive_.replies(file_id_, comment_id_);
    espadin::reply data;
    data.content("This comment sucks");
    auto crep = rep->create(std::move(data), "id")->run();
    ASSERT_TRUE(crep);
    ASSERT_TRUE(crep->id());
    rep->del(*crep->id())->run();
    EXPECT_THROW((rep->get(*crep->id(), "*")->run()), espadin::drive_exception);
}