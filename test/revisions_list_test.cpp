#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>
#include <fstream>

namespace
{

class revisions_list : public testing::Test, public espadin::test::base
{
protected:
    virtual void SetUp() override
    {
        std::string name("revisions_list");
        file_id_ = create_doc(name);
        for (const auto& txt : { "one", "two", "three" })
        {
            auto tmp = std::filesystem::temp_directory_path() / "revisions_list_test.txt";
            std::ofstream out(tmp);
            out << txt;
            out.close();
            espadin::file metadata;
            drive_.files()->update(file_id_, std::move(metadata), tmp)->run();
            std::filesystem::remove(tmp);
        }
    }

    virtual void TearDown() override
    {
        trash(file_id_);
    }

    std::string file_id_;
};

}

TEST_F(revisions_list, pages)
{
    auto lst = drive_.revisions(file_id_)->list();
    auto reply = lst->fields("*")
                     .page_size(3)
                     .run();
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->next_page_token());
    ASSERT_TRUE(reply->revisions());
    EXPECT_EQ(3, reply->revisions()->size());
    reply = lst->page_token(*reply->next_page_token()).run();
    ASSERT_TRUE(reply);
    ASSERT_FALSE(reply->next_page_token());
    ASSERT_TRUE(reply->revisions());
    EXPECT_EQ(1, reply->revisions()->size());
}