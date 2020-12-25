#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class comments_update : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("comments_update")
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

TEST_F(comments_update, content)
{
    auto cmts = drive_.comments();
    auto reply = cmts->create(file_id_, "This is a mistake", "id")->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->id());
    auto comment_id = *reply->id();
    reply = cmts->update(file_id_, comment_id, "This is fixed", "content")->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->content());
    EXPECT_STREQ("This is fixed", reply->content()->c_str());
}
