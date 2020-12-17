#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>
#include <fstream>

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
            .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and 'root' in parents");
        auto reply = lst->run();
        ASSERT_TRUE(reply->files());
        ASSERT_EQ(1, reply->files()->size());
        ASSERT_TRUE(reply->files()->at(0).id());
        parent_ = reply->files()->at(0).id().value();
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
    auto create = files_->create(std::move(f));
    auto reply = create->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}

TEST_F(files_create, small)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_small.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 2 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_})
      .name(f.filename().string());
    auto reply = files_->create(std::move(md), f)->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}

TEST_F(files_create, small_with_progress)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_small_with_progress.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 2 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_})
      .name(f.filename().string());
    auto crt = files_->create(std::move(md), f);
    crt->progress_callback([] (double pct) { std::cout << pct << '%' << std::endl; });
    auto reply = crt->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}

TEST_F(files_create, large)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_large.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 6 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_})
      .name(f.filename().string());
    auto reply = files_->create(std::move(md), f)->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}

TEST_F(files_create, large_with_progress)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_large_with_progress.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 6 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_})
      .name(f.filename().string());
    auto crt = files_->create(std::move(md), f);
    crt->progress_callback([] (double pct) { std::cout << pct << '%' << std::endl; });
    auto reply = crt->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->id());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
}
