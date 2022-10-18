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
  ../../src/request/parser/chunked_parser.cpp 
  ../../src/request/parser/header_field_parser.cpp 
  ../../src/request/parser/request_line_parser.cpp 
  ../../src/request/parser/request_parser.cpp 
  ../../src/request/parser/request_target_parser.cpp 
  ../../src/request/request_validator.cpp 
  ../../src/request/request.cpp 
  ../../src/request/parser/uri_host_parser.cpp 
  ../../src/request/uri.cpp 

    ../../src/config/config_interface.cpp 
		../../src/config/setup.cpp 
		../../src/config/server_name.cpp 
		../../src/config/server_context.cpp
    ../../src/config/server_context_verification.cpp
    ../../src/config/server_context_setters.cpp
		../../src/config/listen.cpp 
		../../src/config/location_context.cpp 
    ../../src/config/location_context_verification.cpp
    ../../src/config/location_context_setters.cpp
		nginx_config.cpp 
    ../../src/config/nginx_config_file_handler.cpp
    ../../src/config/nginx_config_get_servers.cpp
		../../src/config/directive_validation/client_max_body_size.cpp 
		../../src/config/directive_validation/allowed_methods.cpp 
		../../src/config/directive_validation/autoindex.cpp 
		../../src/config/directive_validation/cgi_pass.cpp 
    ../../src/config/directive_validation/cgi_pass_parser.cpp 
		../../src/config/directive_validation/index.cpp 
		../../src/config/directive_validation/location_uri.cpp 
		../../src/config/directive_validation/return_dir.cpp 
		../../src/config/directive_validation/root.cpp

    ../../src/resolved_target/server_selection.cpp
    ../../src/resolved_target/resolved_path.cpp
		../../src/resolved_target/location_selection.cpp
		../../src/resolved_target/target_config.cpp

    ../../src/cgi/cgi.cpp
    cgi_argv_envp.cpp 
    ../../src/cgi/cgi_file_validation.cpp 
    cgi_parent_child.cpp 
    ../../src/cgi/cgi_pathfinder.cpp

    ../../src/utils/file_handling.cpp
    ../../src/utils/is_functions.cpp
    ../../src/utils/request_utils.cpp
    ../../src/utils/cgi_utils.cpp
		../../src/utils/config_utils.cpp 
)
# Link test executable against gtest or gtest_main or your own main (not recommended)
target_link_libraries(
  try_test # test executable name
  gtest_main
)

# Enables CMake's test runner to discover tests included in binary
include(GoogleTest)
gtest_discover_tests(try_test) # test executable name