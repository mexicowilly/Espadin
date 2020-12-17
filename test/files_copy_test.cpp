#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>
#include <fstream>

extern std::string ACCESS_TOKEN;

namespace
{

class files_copy : public testing::Test
{
public:
    files_copy()
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
        std::filesystem::path f(std::filesystem::temp_directory_path() / "copy.txt");
        std::ofstream out(f);
        out << "My dog has fleas";
        out.close();
        espadin::file metadata;
        metadata.name(f.filename().string())
                .parents({parent_});
        auto crt_reply = files_->create(std::move(metadata), f)->run();
        ASSERT_TRUE(crt_reply->id());
        to_copy_ = *crt_reply->id();
        std::filesystem::remove(f);
    }

    virtual void TearDown() override
    {
        espadin::file metadata;
        metadata.trashed(true);
        files_->update(to_copy_, std::move(metadata))->run();
        if (!copied_.empty())
        {
            espadin::file metadata2;
            metadata2.trashed(true);
            files_->update(copied_, std::move(metadata2))->run();
        }
    }

    espadin::drive drive_;
    std::unique_ptr<espadin::files_group> files_;
    std::string parent_;
    std::string to_copy_;
    std::string copied_;
};

}

TEST_F(files_copy, simple)
{
    espadin::file metadata;
    auto reply = files_->copy(to_copy_, std::move(metadata))->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->id());
    copied_ = *reply->id();
    EXPECT_NE(to_copy_, copied_);
}

TEST_F(files_copy, format_change)
{
    espadin::file metadata;
    metadata.name("doc copy")
            .mime_type("application/vnd.google-apps.document");
    auto reply = files_->copy(to_copy_, std::move(metadata))->run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->id());
    copied_ = *reply->id();
    EXPECT_NE(to_copy_, copied_);
}