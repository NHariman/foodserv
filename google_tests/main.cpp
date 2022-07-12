#include <gtest/gtest.h>

TEST()

int		main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// clang++ google_tests/main.cpp -std=c++11