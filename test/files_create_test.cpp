#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>

extern std::string ACCESS_TOKEN;

namespace
{

class files_create : public testing::Test
{
public:
    files_create()
        : drive_(ACCESS_TOKEN)
    {
    }

protected:
    virtual void SetUp() override
    {
        files_ = std::move(drive_.files());
        auto lst = files_->list();
        lst->fields("files/id")
            .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder'");
        auto reply = lst->run();
        ASSERT_EQ(1, reply->files().size());
        ASSERT_TRUE(reply->files()[0].id());
        parent_ = reply->files()[0].id().value();
    }

    espadin::drive drive_;
    std::unique_ptr<espadin::files_group> files_;
    std::string parent_;
};

}

TEST_F(files_create, empty)
{
    espadin::file f;
    f.parents({parent_});
    auto create = files_->create(f);
    auto reply = create->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}

TEST_F(files_create, char_data)
{
    espadin::file f;
    f.parents({parent_})
     .name("my stuff.json")
     .mime_type("application/json");
    std::vector<std::byte> data;
    std::string str("{ \"hello\": \"goodbye\" }");
    for (auto c : str)
        data.push_back(static_cast<std::byte>(c));
    auto create = files_->create(f, data);
    auto reply = create->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}
