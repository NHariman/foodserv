if(EXISTS "/Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build/try_test[1]_tests.cmake")
  include("/Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build/try_test[1]_tests.cmake")
else()
  add_test(try_test_NOT_BUILT try_test_NOT_BUILT)
endif()
