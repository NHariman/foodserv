cmake_minimum_required(VERSION 3.12)

project(test_project)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests print_string.cpp main.cpp)
#^ put all the files you want to compile here, you need the main
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)