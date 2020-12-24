#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class comments_delete : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        espadin::file metadata;
        metadata.parents({parent_id})
                .name("comments_delete")
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

TEST_F(comments_delete, delete_one)
{
    auto cmts = drive_.comments();
    auto reply = cmts->create(file_id_, "This is a comment", "id")->run();
    ASSERT_TRUE(reply->id());
    cmts->del(file_id_, *reply->id())->run();
    EXPECT_THROW(cmts->get(file_id_, *reply->id(), "id")->run(), espadin::drive_exception);
}