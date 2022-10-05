cmake_minimum_required(VERSION 3.14)
project(gtest_test)

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
  try_test # test executable name
  try_test.cpp
  ../../request/chunked_parser.cpp 
  ../../request/header_field_parser.cpp 
  ../../request/request_line_parser.cpp 
  ../../request/request_parser.cpp 
  ../../request/request_target_parser.cpp 
  ../../request/request_validator.cpp 
  ../../request/request.cpp 
  ../../request/uri_host_parser.cpp 
  ../../request/uri.cpp 

    ../../config/config_interface.cpp 
		../../config/setup.cpp 
		../../config/server_name.cpp 
		../../config/server_context.cpp 
		../../config/listen.cpp 
		../../config/location_context.cpp 
		nginx_config.cpp 
		../../config/config_utils.cpp 
		../../config/directive_validation/client_max_body_size.cpp 
		../../config/directive_validation/allowed_methods.cpp 
		../../config/directive_validation/autoindex.cpp 
		../../config/directive_validation/error_page.cpp 
		../../config/directive_validation/cgi_pass.cpp 
		../../config/directive_validation/index.cpp 
		../../config/directive_validation/location_uri.cpp 
		../../config/directive_validation/return_dir.cpp 
		../../config/directive_validation/root.cpp

    ../../resolved_target/server_selection.cpp
    ../../resolved_target/resolved_path.cpp
		../../resolved_target/location_selection.cpp
		../../resolved_target/target_config.cpp

    ../cgi.cpp
    ../cgi_argv_envp.cpp 
    ../cgi_file_validation.cpp 
    ../cgi_parent_child.cpp 
    ../cgi_pathfinder.cpp

    ../../utils/file_handling.cpp
    ../../utils/is_functions.cpp
    ../../utils/request_utils.cpp
    ../../utils/cgi_utils.cpp
)
# Link test executable against gtest or gtest_main or your own main (not recommended)
target_link_libraries(
  try_test # test executable name
  gtest_main
)

# Enables CMake's test runner to discover tests included in binary
include(GoogleTest)
gtest_discover_tests(try_test) # test executable name