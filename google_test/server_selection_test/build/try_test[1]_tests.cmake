add_test( ServerSelectionTest.TestConfig1 /Users/sannealbreghs/Desktop/foodserv/google_test/server_selection_test/build/try_test [==[--gtest_filter=ServerSelectionTest.TestConfig1]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerSelectionTest.TestConfig1 PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/server_selection_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( try_test_TESTS ServerSelectionTest.TestConfig1)
