#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>

extern std::string ACCESS_TOKEN;

TEST(files, list)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto fl = drv.files()->list();
    fl->fields("files/id")
       .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and 'root' in parents");
    auto reply = fl->run();
    ASSERT_TRUE(reply->files());
    ASSERT_EQ(1, reply->files()->size());
    ASSERT_TRUE(reply->files()->at(0).id());
    std::cout << "Found folder 'Espadin Test': " << reply->files()->at(0).id().value() << std::endl;
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

TEST(files, list_non_existent)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto fl = drv.files()->list();
    fl->fields("files/id")
       .query("name='monkey dog' and 'root' in parents");
    auto reply = fl->run();
    ASSERT_TRUE(reply->files());
    EXPECT_TRUE(reply->files()->empty());
}