#include <gtest/gtest.h>
#include <chucho/log.hpp>
#include <cstdlib>

std::string ACCESS_TOKEN;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    if (argc == 2)
    {
        ACCESS_TOKEN = argv[1];
    }
    else
    {
        auto lgr = chucho::logger::get("espadin.test");
        CHUCHO_ERROR(lgr, "Expected one non-gtest argument for the access token");
        return EXIT_FAILURE;
    }
    return RUN_ALL_TESTS();
}