add_test([=[AllowedMethodsTest.ValidInput]=]  /Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build/try_test [==[--gtest_filter=AllowedMethodsTest.ValidInput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AllowedMethodsTest.ValidInput]=]  PROPERTIES WORKING_DIRECTORY /Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[AllowedMethodsTest.InvalidInput]=]  /Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build/try_test [==[--gtest_filter=AllowedMethodsTest.InvalidInput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AllowedMethodsTest.InvalidInput]=]  PROPERTIES WORKING_DIRECTORY /Users/nhariman/webserv_nginxconfig/google_test/allowed_method_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  try_test_TESTS AllowedMethodsTest.ValidInput AllowedMethodsTest.InvalidInput)