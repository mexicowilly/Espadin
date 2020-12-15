#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>
#include <fstream>

extern std::string ACCESS_TOKEN;

namespace
{

class files_update : public testing::Test
{
public:
    files_update()
        : drive_(ACCESS_TOKEN)
    {
    }

protected:
    virtual void SetUp() override
    {
        files_ = std::move(drive_.files());
        auto lst = files_->list();
        lst->fields("files/id")
        .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and 'root' in parents");
        auto reply = lst->run();
        ASSERT_EQ(1, reply->files().size());
        ASSERT_TRUE(reply->files()[0].id());
        parent_ = reply->files()[0].id().value();
        espadin::file f;
        f.parents({parent_});
        auto created = files_->create(std::move(f))->run();
        ASSERT_TRUE(created->id());
        to_update_ = *created->id();
    }

    virtual void TearDown() override
    {
        espadin::file f;
        f.trashed(true);
        files_->update(to_update_, std::move(f))->run();
    }

    espadin::drive drive_;
    std::unique_ptr<espadin::files_group> files_;
    std::string parent_;
    std::string to_update_;
};

}

TEST_F(files_update, empty)
{
    std::string new_name("are you serious?");
    espadin::file metadata;
    metadata.name(new_name);
    auto reply = files_->update(to_update_, std::move(metadata))->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_EQ(new_name, *reply->name());
    EXPECT_TRUE(reply->mime_type());
}