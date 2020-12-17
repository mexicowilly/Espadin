#include <gtest/gtest.h>
#include <espadin/drive.hpp>

extern std::string ACCESS_TOKEN;

TEST(generate_ids, simple)
{
    espadin::drive drv(ACCESS_TOKEN);
    auto gen = drv.files()->generate_ids();
    auto reply = gen->count(3)
                     .fields("*")
                     .run();
    ASSERT_TRUE(reply->ids());
    ASSERT_TRUE(reply->kind());
    ASSERT_TRUE(reply->space());
    EXPECT_EQ(3, reply->ids()->size());
    reply = gen->count(1)
                .fields("ids")
                .run();
    ASSERT_TRUE(reply->ids());
    ASSERT_FALSE(reply->kind());
    ASSERT_FALSE(reply->space());
    EXPECT_EQ(1, reply->ids()->size());
}