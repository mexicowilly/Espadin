#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <iostream>

extern std::string ACCESS_TOKEN;

TEST(files, list)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto fl = drv.files()->list();
    fl->corpora("user")
       .fields("files/id")
       .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder'");
    auto reply = fl->run();
    ASSERT_GT(reply->files().size(), 0);
    std::string folder = reply->files()[0].id();
    std::cout << "Found folder 'Espadin Test': " << folder << std::endl;
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