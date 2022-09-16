add_test( OnlyIP.CorrectInput /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build/try_test [==[--gtest_filter=OnlyIP.CorrectInput]==] --gtest_also_run_disabled_tests)
set_tests_properties( OnlyIP.CorrectInput PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( OnlyPort.CorrectInput /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build/try_test [==[--gtest_filter=OnlyPort.CorrectInput]==] --gtest_also_run_disabled_tests)
set_tests_properties( OnlyPort.CorrectInput PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Both.CorrectInput /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build/try_test [==[--gtest_filter=Both.CorrectInput]==] --gtest_also_run_disabled_tests)
set_tests_properties( Both.CorrectInput PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ListenTestInvalid.Exceptions /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build/try_test [==[--gtest_filter=ListenTestInvalid.Exceptions]==] --gtest_also_run_disabled_tests)
set_tests_properties( ListenTestInvalid.Exceptions PROPERTIES WORKING_DIRECTORY /Users/sannealbreghs/Desktop/foodserv/google_test/listen_test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( try_test_TESTS OnlyIP.CorrectInput OnlyPort.CorrectInput Both.CorrectInput ListenTestInvalid.Exceptions)