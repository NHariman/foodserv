add_test( RootTest.RootTesting /Users/sannealbreghs/Desktop/foodserv/google_test/resolved_path_test/build/try_test [==[--gtest_filter=RootTest.RootTesting]==] --gtest_also_run_disabled_tests)
set_tests_properties( RootTest.RootTesting PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/resolved_path_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( try_test_TESTS RootTest.RootTesting)
