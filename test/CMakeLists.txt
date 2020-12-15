ADD_EXECUTABLE(unit-test
               files_create_test.cpp
               files_delete_test.cpp
               files_get_test.cpp
               files_list_test.cpp
               files_update_test.cpp
               harness.cpp)
TARGET_LINK_LIBRARIES(unit-test espadin GTest::GTest)