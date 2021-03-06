#include <gtest/gtest.h>
#include "base_test.hpp"
#include <espadin/exception.hpp>

namespace
{

class files_delete : public testing::Test, public espadin::test::base
{
};

}

TEST_F(files_delete, one)
{
    auto files = drive_.files();
    espadin::file f;
    f.parents({parent_id});
    auto md = files->create(std::move(f))->run();
    ASSERT_TRUE(md->id());
    files->del(*md->id())->run();
    EXPECT_THROW(files->get(*md->id())->run(), espadin::drive_exception);
}