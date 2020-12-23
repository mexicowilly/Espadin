#include <gtest/gtest.h>
#include "base_test.hpp"
#include <iostream>
#include <fstream>

namespace
{

class files_update : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        files_ = drive_.files();
        espadin::file f;
        f.parents({parent_id});
        auto created = files_->create(std::move(f))->run();
        ASSERT_TRUE(created->id());
        to_update_ = *created->id();
    }

    virtual void TearDown() override
    {
        trash(to_update_);
    }

    std::unique_ptr<espadin::files_group> files_;
    std::string to_update_;
};

}

TEST_F(files_update, contents)
{
    std::filesystem::path f(std::filesystem::temp_directory_path() / "files_update_contents.txt");
    std::ofstream stream(f);
    for (int i = 0; i < 2 * 1024 * 1024; i++)
        stream << static_cast<char>((i % 32) + 32);
    stream.close();
    espadin::file metadata;
    metadata.name(f.filename().string());
    files_->update(to_update_, std::move(metadata), f)->run();
    auto get = files_->get(to_update_);
    auto reply = get->fields("name,size").run();
    EXPECT_TRUE(reply->name());
    EXPECT_EQ(f.filename().string(), *reply->name());
    EXPECT_TRUE(reply->size());
    EXPECT_EQ(std::filesystem::file_size(f), *reply->size());
    std::filesystem::remove(f);
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