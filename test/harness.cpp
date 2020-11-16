#include <gtest/gtest.h>
#include <chucho/log.hpp>
#include <espadin/finalize.hpp>
#include <chucho/finalize.hpp>
#include <cstdlib>

std::string ACCESS_TOKEN;

int main(int argc, char* argv[])
{
    int rc = EXIT_SUCCESS;
    testing::InitGoogleTest(&argc, argv);
    if (argc == 2)
    {
        ACCESS_TOKEN = argv[1];
        rc = RUN_ALL_TESTS();
    }
    else
    {
        auto lgr = chucho::logger::get("espadin.test");
        CHUCHO_ERROR(lgr, "Expected one non-gtest argument for the access token");
        rc = EXIT_FAILURE;
    }
    espadin::finalize();
    chucho::finalize();
    return rc;
}