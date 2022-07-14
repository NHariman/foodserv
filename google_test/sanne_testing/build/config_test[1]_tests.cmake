add_test( ConfigTest.BasicAssertions /Users/sannealbreghs/Desktop/foodserv/google_test/sanne_testing/build/config_test [==[--gtest_filter=ConfigTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( ConfigTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/sanne_testing/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( config_test_TESTS ConfigTest.BasicAssertions)
