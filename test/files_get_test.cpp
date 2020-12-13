#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>
#include <fstream>
#include <iterator>

extern std::string ACCESS_TOKEN;

namespace
{

class files_get : public testing::Test
{
public:
    files_get()
        : drive_(ACCESS_TOKEN)
    {
    }

protected:
    virtual void SetUp() override
    {
        files_ = std::move(drive_.files());
        auto lst = files_->list();
        lst->fields("files/id")
            .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and parents in 'root'");
        auto reply = lst->run();
        ASSERT_EQ(1, reply->files().size());
        ASSERT_TRUE(reply->files()[0].id());
        parent_ = reply->files()[0].id().value();
    }

    bool files_are_equal(const std::filesystem::path& partial, const std::filesystem::path& full)
    {
        bool result = false;
        auto one = std::filesystem::temp_directory_path() / partial;
        if (std::filesystem::file_size(one) == std::filesystem::file_size(full))
        {
            std::ifstream one_in(one);
            std::ifstream two_in(full);
            result = std::equal(std::istream_iterator<char>(one_in),
                                std::istream_iterator<char>(),
                                std::istream_iterator<char>(two_in));
        }
        return result;
    }

    std::string create_file(const std::filesystem::path& name)
    {
        auto full = std::filesystem::temp_directory_path() / name;
        std::ofstream stream(full);
        for (int i = 0; i < 2 * 1024 * 1024; i++)
            stream << static_cast<char>((i % 32) + 32);
        stream.close();
        espadin::file meta;
        meta.name(name.string())
            .parents({parent_});
        auto reply = files_->create(std::move(meta), full)->run();
        EXPECT_TRUE(reply);
        EXPECT_TRUE(reply->id());
        return *reply->id();
    }

    void delete_file(const std::filesystem::path& name)
    {
        std::filesystem::remove(std::filesystem::temp_directory_path() / name);
    }

    std::unique_ptr<espadin::files_group> files_;

private:
    espadin::drive drive_;
    std::string parent_;
};

}

TEST_F(files_get, meta)
{
    std::filesystem::path fname("files_get_meta.txt");
    auto id = create_file(fname);
    auto get = files_->get(id);
    get->fields("name");
    auto reply = get->run();
    delete_file(fname);
    ASSERT_TRUE(reply);
    ASSERT_TRUE(reply->name());
    EXPECT_STREQ(fname.filename().c_str(), reply->name()->c_str());
}

TEST_F(files_get, contents)
{
    std::filesystem::path fname("files_get_meta.txt");
    auto id = create_file(fname);
    std::filesystem::path dl_name(std::filesystem::temp_directory_path() / "files_get_meta_to_compare.txt");
    std::ofstream out(dl_name);
    auto get = files_->get(id, out);
    auto reply = get->run();
    out.close();
    EXPECT_FALSE(reply);
    EXPECT_TRUE(files_are_equal(fname, dl_name));
    std::filesystem::remove(dl_name);
    delete_file(fname);
}