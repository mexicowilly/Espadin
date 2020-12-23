#include <gtest/gtest.h>
#include "base_test.hpp"
#include <iostream>
#include <fstream>

namespace
{

class files_copy : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        files_ = drive_.files();
        std::filesystem::path f(std::filesystem::temp_directory_path() / "copy.txt");
        std::ofstream out(f);
        out << "My dog has fleas";
        out.close();
        espadin::file metadata;
        metadata.name(f.filename().string())
                .parents({parent_id});
        auto crt_reply = files_->create(std::move(metadata), f)->run();
        ASSERT_TRUE(crt_reply->id());
        to_copy_ = *crt_reply->id();
        std::filesystem::remove(f);
    }

    virtual void TearDown() override
    {
        trash(to_copy_);
        if (!copied_.empty())
            trash(copied_);
    }

    std::unique_ptr<espadin::files_group> files_;
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