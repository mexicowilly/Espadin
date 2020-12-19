#include <gtest/gtest.h>
#include <espadin/drive.hpp>

extern std::string ACCESS_TOKEN;

TEST(about, all)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto reply = drv.about_drive("*");
    ASSERT_TRUE(reply);
    EXPECT_TRUE(reply->can_create_drives());
    EXPECT_TRUE(reply->can_create_team_drives());
    EXPECT_TRUE(reply->drive_themes());
    EXPECT_TRUE(reply->export_formats());
    EXPECT_TRUE(reply->import_formats());
    ASSERT_TRUE(reply->kind());
    EXPECT_STREQ("drive#about", reply->kind()->c_str());
    EXPECT_TRUE(reply->max_import_sizes());
    EXPECT_TRUE(reply->max_upload_size());
    EXPECT_TRUE(reply->team_drive_themes());
}