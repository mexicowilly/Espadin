ADD_EXECUTABLE(unit-test
               files_create_test.cpp
               files_list_test.cpp
               harness.cpp)
TARGET_LINK_LIBRARIES(unit-test espadin GTest::GTest)