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

TEST(OnlyIP, CorrectInput) {
  Listen  test1("localhost");
	EXPECT_EQ(test1.getIpNumber(), "127.0.0.1");
	EXPECT_EQ(test1.getPortNumber(), "80");

  Listen  test2("*");
	EXPECT_EQ(test2.getIpNumber(), "0");
	EXPECT_EQ(test1.getPortNumber(), "80");
  

  // TO DO : testing for invalid IP's as in [1:2:3]

}

TEST(OnlyPort, CorrectInput) {
  Listen  test1("8000");
	EXPECT_EQ(test1.getIpNumber(), "0");
	EXPECT_EQ(test1.getPortNumber(), "8000");

  Listen  test2("12345");
  EXPECT_EQ(test2.getIpNumber(), "0");
  EXPECT_EQ(test2.getPortNumber(), "12345");

  // TO DO: testing for invalid ports like 3123123124
}

TEST(Both, CorrectInput) {
	Listen  test1("127.0.0.1:8000");
	EXPECT_EQ(test1.getIpNumber(), "127.0.0.1");
	EXPECT_EQ(test1.getPortNumber(), "8000");

  Listen  test2("*:8000");
	EXPECT_EQ(test2.getIpNumber(), "0");
	EXPECT_EQ(test2.getPortNumber(), "8000"); 
  
  Listen  test3("");
	EXPECT_EQ(test3.getIpNumber(), "0");
	EXPECT_EQ(test3.getPortNumber(), "80");

  Listen  test4("localhost:10");
	EXPECT_EQ(test4.getIpNumber(), "127.0.0.1");
	EXPECT_EQ(test4.getPortNumber(), "10");
}


TEST(ListenTestInvalid, Exceptions) {
  EXPECT_THROW({
    Listen test("crap:crap");
  }, Listen::InvalidIpException);
  EXPECT_THROW({
    Listen  test("localhost:localhost");
  }, Listen::InvalidPortException);
  EXPECT_THROW({
    Listen  test(":0");
  }, Listen::InvalidIpException);
  EXPECT_THROW({
    Listen  test(":");
  }, Listen::InvalidIpException);
  EXPECT_THROW({
    Listen  test("0:");
  }, Listen::InvalidPortException);
  EXPECT_THROW({
    Listen  test1("*:*");
  }, Listen::InvalidPortException);
  EXPECT_THROW({
    Listen  test2("-1");
  }, Listen::InvalidPortException);
}