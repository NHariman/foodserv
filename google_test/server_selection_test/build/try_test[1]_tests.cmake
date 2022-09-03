add_test( TestFake.Test /Users/sannealbreghs/Desktop/foodserv/google_test/server_selection_test/build/try_test [==[--gtest_filter=TestFake.Test]==] --gtest_also_run_disabled_tests)
set_tests_properties( TestFake.Test PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/server_selection_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( try_test_TESTS TestFake.Test)
