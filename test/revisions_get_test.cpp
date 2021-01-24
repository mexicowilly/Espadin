#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>
#include <fstream>

namespace
{

class revisions_get : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        file_id_ = create_doc("revisions_get");
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(revisions_get, one)
{
    auto revisions = drive_.revisions(file_id_);
    auto lst = revisions->list()->fields("revisions/id").run();
    ASSERT_TRUE(lst);
    ASSERT_EQ(1, lst->revisions()->size());
    ASSERT_TRUE(lst->revisions()->at(0).id());
    auto rev = revisions->get(*lst->revisions()->at(0).id())->fields("*").run();
    ASSERT_TRUE(rev);
    ASSERT_TRUE(rev->kind());
    EXPECT_STREQ("drive#revision", rev->kind()->c_str());
    ASSERT_TRUE(rev->id());
    EXPECT_STREQ(lst->revisions()->at(0).id()->c_str(), rev->id()->c_str());
    ASSERT_TRUE(rev->mime_type());
    EXPECT_STREQ("application/vnd.google-apps.document", rev->mime_type()->c_str());
    EXPECT_TRUE(rev->modified_time());
    EXPECT_FALSE(rev->keep_forever());
    ASSERT_TRUE(rev->published());
    EXPECT_FALSE(*rev->published());
    EXPECT_FALSE(rev->published_link());
    EXPECT_FALSE(rev->publish_auto());
    EXPECT_FALSE(rev->published_outside_domain());
    EXPECT_TRUE(rev->last_modifying_user());
    EXPECT_FALSE(rev->original_filename());
    EXPECT_FALSE(rev->md5_checksum());
    EXPECT_FALSE(rev->size());
    ASSERT_TRUE(rev->export_links());
    EXPECT_EQ(8, rev->export_links()->size());
}
