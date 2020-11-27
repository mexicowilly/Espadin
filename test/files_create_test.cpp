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
    create->run();
//    espadin::drive drv(ACCESS_TOKEN);
//    auto fl = drv.files()->list();
//    fl->fields("files/id")
//    .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder'");
//    auto reply = fl->run();
//    ASSERT_EQ(1, reply->files().size());
//    ASSERT_TRUE(reply->files()[0].id());
//    std::cout << "Found folder 'Espadin Test': " << reply->files()[0].id().value() << std::endl;
//    do
//    {
//        reply = fl->run();
//        for (const auto& f : reply->files())
//            names.push_back(f.name());
//        if (reply->next_page_token().empty())
//            break;
//        fl->page_token(reply->next_page_token());
//    } while (true);
}
