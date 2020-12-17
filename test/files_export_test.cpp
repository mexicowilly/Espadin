#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>
#include <fstream>

extern std::string ACCESS_TOKEN;

namespace
{

class files_export : public testing::Test
{
public:
    files_export()
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
        ASSERT_TRUE(reply->files());
        ASSERT_EQ(1, reply->files()->size());
        ASSERT_TRUE(reply->files()->at(0).id());
        parent_ = reply->files()->at(0).id().value();
        std::filesystem::path f(std::filesystem::temp_directory_path() / "export.txt");
        std::ofstream out(f);
        out << "My dog has fleas";
        out.close();
        espadin::file metadata;
        metadata.name(f.filename().string())
                .mime_type("application/vnd.google-apps.document")
                .parents({parent_});
        auto crt_reply = files_->create(std::move(metadata), f)->run();
        ASSERT_TRUE(crt_reply->id());
        to_export_ = *crt_reply->id();
        std::filesystem::remove(f);
    }

    virtual void TearDown() override
    {
        espadin::file metadata;
        metadata.trashed(true);
        files_->update(to_export_, std::move(metadata))->run();
    }

    espadin::drive drive_;
    std::unique_ptr<espadin::files_group> files_;
    std::string parent_;
    std::string to_export_;
};

}

TEST_F(files_export, to_text)
{
    std::ostringstream out;
    files_->exp(to_export_, "text/plain", out)->run();
    auto str = out.str();
    ASSERT_EQ(19, str.length());
    EXPECT_EQ(static_cast<char>(0xef), str[0]);
    EXPECT_EQ(static_cast<char>(0xbb), str[1]);
    EXPECT_EQ(static_cast<char>(0xbf), str[2]);
    EXPECT_STREQ("My dog has fleas", str.substr(3).c_str());
}