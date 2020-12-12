#include <gtest/gtest.h>
#include <espadin/drive.hpp>
#include <espadin/exception.hpp>
#include <iostream>

extern std::string ACCESS_TOKEN;

TEST(files_delete, one)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto files = drv.files();
    auto lst = files->list();
    lst->fields("files/id")
        .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and parents in 'root'");
    auto list_reply = lst->run();
    ASSERT_EQ(1, list_reply->files().size());
    ASSERT_TRUE(list_reply->files()[0].id());
    auto parent = list_reply->files()[0].id().value();
    espadin::file f;
    f.parents({parent});
    auto md = files->create(f)->run();
    ASSERT_TRUE(md->id());
    files->del(*md->id())->run();
    try
    {
        files->get(*md->id())->run();
    }
    catch (const espadin::drive_exception& e)
    {
        ASSERT_EQ(404, e.code());
    }
}