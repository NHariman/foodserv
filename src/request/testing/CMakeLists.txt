cmake_minimum_required(VERSION 3.14)
project(request_test)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# List all test files you want to compile
add_executable(
  request_test # test executable name
  request_test.cpp
  ../uri.cpp
  ../request_utils.cpp
  ../uri_state_parser.cpp
)
# Link test executable against gtest or gtest_main or your own main (not recommended)
target_link_libraries(
  request_test # test executable name
  gtest_main
)

# Enables CMake's test runner to discover tests included in binary
include(GoogleTest)
gtest_discover_tests(request_test) # test executable name