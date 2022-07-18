# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-src"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-build"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/nhariman/codam/webserv/google_test/test_error_page/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
