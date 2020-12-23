#include <gtest/gtest.h>
#include "base_test.hpp"
#include <iostream>
#include <fstream>

namespace
{

class files_create : public testing::Test, public espadin::test::base
{
};

}

TEST_F(files_create, empty)
{
    espadin::file f;
    f.parents({parent_id});
    auto create = drive_.files()->create(std::move(f));
    auto reply = create->run();
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
    ASSERT_TRUE(reply->id());
    trash(*reply->id());
}

TEST_F(files_create, small)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_small.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 2 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_id})
      .name(f.filename().string());
    auto reply = drive_.files()->create(std::move(md), f)->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
    ASSERT_TRUE(reply->id());
    trash(*reply->id());
}

TEST_F(files_create, small_with_progress)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_small_with_progress.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 2 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_id})
      .name(f.filename().string());
    auto crt = drive_.files()->create(std::move(md), f);
    crt->progress_callback([] (double pct) { std::cout << pct << '%' << std::endl; });
    auto reply = crt->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
    ASSERT_TRUE(reply->id());
    trash(*reply->id());
}

TEST_F(files_create, large)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_large.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 6 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_id})
      .name(f.filename().string());
    auto reply = drive_.files()->create(std::move(md), f)->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
    ASSERT_TRUE(reply->id());
    trash(*reply->id());
}

TEST_F(files_create, large_with_progress)
{
    std::filesystem::path f = std::filesystem::temp_directory_path() / "files_create_large_with_progress.txt";
    std::ofstream stream(f);
    for (int i = 0; i < 6 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file md;
    md.parents({parent_id})
      .name(f.filename().string());
    auto crt = drive_.files()->create(std::move(md), f);
    crt->progress_callback([] (double pct) { std::cout << pct << '%' << std::endl; });
    auto reply = crt->run();
    std::filesystem::remove(f);
    EXPECT_TRUE(reply->kind());
    EXPECT_TRUE(reply->name());
    EXPECT_TRUE(reply->mime_type());
    ASSERT_TRUE(reply->id());
    trash(*reply->id());
}
