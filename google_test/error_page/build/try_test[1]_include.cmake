if(EXISTS "/Users/nhariman/codam/webserv/google_test/error_page/build/try_test[1]_tests.cmake")
  include("/Users/nhariman/codam/webserv/google_test/error_page/build/try_test[1]_tests.cmake")
else()
  add_test(try_test_NOT_BUILT try_test_NOT_BUILT)
endif()
