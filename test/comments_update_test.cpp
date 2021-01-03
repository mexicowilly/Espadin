#include <gtest/gtest.h>
#include "base_test.hpp"

namespace
{

class comments_update : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("comments_update");
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
    auto cmts = drive_.comments(file_id_);
    auto reply = cmts->create("This is a mistake", "id")->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->id());
    auto comment_id = *reply->id();
    reply = cmts->update(comment_id, "This is fixed", "content")->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->content());
    EXPECT_STREQ("This is fixed", reply->content()->c_str());
}
