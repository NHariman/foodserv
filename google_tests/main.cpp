#include <gtest/gtest.h>

/*
**	Test for the Listen and Servername part.
**	First of all I want to test if my IP and Host and ServerNames are set correctly
**	Then I want to test if there are multiple server blocks, if the correct one is chosen.
*/

TEST()

int		main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// clang++ google_tests/main.cpp -std=c++11