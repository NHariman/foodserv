cmake_minimum_required(VERSION 3.14)
project(resolved_path_test)

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

set(EXEC resolved_path_test) # test executable name

file(GLOB SRCS CONFIGURE_DEPENDS
  "*.cpp"
	"../../src/cgi/*.cpp"
  "../../src/config/*.cpp"
  "../../src/config/directive_validation/*.cpp"
	"../../src/connection/*.cpp"
	"../../src/err/*.cpp"
  "../../src/request/*.cpp"
  "../../src/resolved_target/*.cpp"
	"../../src/response/*.cpp"
  "../../src/utils/*.cpp"
	"../../src/config/*.hpp"
  "../../src/config/directive_validation/*.hpp"
	"../../src/connection/*.hpp"
	"../../src/err/*.hpp"
  "../../src/request/*.hpp"
  "../../src/resolved_target/*.hpp"
	"../../src/response/*.hpp"
  "../../src/utils/*.hpp"
)

add_executable(${EXEC})

target_sources(${EXEC}
  PRIVATE
    ${SRCS}
)
target_link_libraries(
  resolved_path_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(resolved_path_test)