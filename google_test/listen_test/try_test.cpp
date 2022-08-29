#include <gtest/gtest.h>
#include "../../src/config/listen.hpp"
// #include <gmock/gmock.h>

// int test(int n);

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

TEST(Listen1, Correct) {
	Listen  test1("127.0.0.1:8000");
	EXPECT_EQ(test1.getIpNumber(), "127.0.0.1");
	EXPECT_EQ(test1.getPortNumber(), "8000");
}

TEST(Listen2, Correct) {
	Listen  test2("8000");
	EXPECT_EQ(test2.getIpNumber(), "0");
	EXPECT_EQ(test2.getPortNumber(), "8000");
}

TEST(ListenTest, Exceptions) {
  EXPECT_THROW({
    Listen test("crap:crap");
  }, Listen::InvalidIpException);
}