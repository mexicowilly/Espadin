#include <gtest/gtest.h>
#include "base_test.hpp"
#include <iostream>
#include <fstream>

namespace
{

class files_export : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        files_ = drive_.files();
        std::filesystem::path f(std::filesystem::temp_directory_path() / "export.txt");
        std::ofstream out(f);
        out << "My dog has fleas";
        out.close();
        espadin::file metadata;
        metadata.name(f.filename().string())
                .mime_type("application/vnd.google-apps.document")
                .parents({parent_id});
        auto crt_reply = files_->create(std::move(metadata), f)->run();
        ASSERT_TRUE(crt_reply->id());
        to_export_ = *crt_reply->id();
        std::filesystem::remove(f);
    }

    virtual void TearDown() override
    {
        trash(to_export_);
    }

    std::unique_ptr<espadin::files_group> files_;
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