cmake_minimum_required(VERSION 3.14)
project(server_selection_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  try_test
  try_test.cpp

  ../../src/config/directive_validation/allowed_methods.cpp
  ../../src/config/directive_validation/autoindex.cpp
  ../../src/config/directive_validation/cgi_pass.cpp
  ../../src/config/directive_validation/client_max_body_size.cpp
  ../../src/config/directive_validation/error_page.cpp
  ../../src/config/directive_validation/index.cpp
  ../../src/config/directive_validation/location_uri.cpp
  ../../src/config/directive_validation/return_dir.cpp
  ../../src/config/directive_validation/root.cpp

  ../../src/config/config_interface.cpp
  ../../src/config/config_utils.cpp
  ../../src/config/listen.cpp
  ../../src/config/location_context.cpp
  ../../src/config/nginx_config.cpp
  ../../src/config/server_context.cpp
  ../../src/config/server_name.cpp
  ../../src/config/setup.cpp

  ../../src/err/error_responses.cpp

  ../../src/request/chunked_parser.cpp
  ../../src/request/header_field_parser.cpp
  ../../src/request/request_line_parser.cpp
  ../../src/request/request_parser.cpp
  ../../src/request/request_target_parser.cpp
  ../../src/request/request_validator.cpp
  ../../src/request/request.cpp
  ../../src/request/uri_host_parser.cpp
  ../../src/request/uri.cpp

  ../../src/resolved_target/location_selection.cpp
  ../../src/resolved_target/resolved_path.cpp
  ../../src/resolved_target/server_selection.cpp
  ../../src/resolved_target/target_config.cpp

  ../../src/utils/file_handling.cpp
  ../../src/utils/is_functions.cpp
  ../../src/utils/request_utils.cpp

)
target_link_libraries(
  try_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(try_test)