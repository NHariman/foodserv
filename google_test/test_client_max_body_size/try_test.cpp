#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "../../src/config/directive_validation/client_max_body_size.hpp"

// int Factorial(int n);

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

TEST(CMBSTest, ValidInputTests) {
  EXPECT_NO_THROW({
    ClientMaxBodySize test("123");
  });
  EXPECT_NO_THROW({
    ClientMaxBodySize test("123m");
  });
  EXPECT_NO_THROW({
    ClientMaxBodySize test("123M");
  });
  EXPECT_NO_THROW({
    ClientMaxBodySize test("2147483647");
  });
  EXPECT_NO_THROW({
    ClientMaxBodySize test("2147483647m");
  });
  EXPECT_NO_THROW({
    ClientMaxBodySize test("2147483647M");
  });
}

TEST(CMBSTest, InvalidInputTests) {
  EXPECT_THROW({
    ClientMaxBodySize test("-123");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123b");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("a123");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123mb");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123MB");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123 1");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123 m");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123m1");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("123Me");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("asbsd");
  }, ClientMaxBodySize::InvalidClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("2147483648");
  }, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("2147483648m");
  }, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
  EXPECT_THROW({
    ClientMaxBodySize test("2147483648M");
  }, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
    EXPECT_THROW({
    ClientMaxBodySize test("");
  }, ClientMaxBodySize::MissingArgumentsException);

}

TEST(CMBSTest, ReturnInputTests) {
  EXPECT_EQ(PrintValue("123"), 123);
  EXPECT_EQ(PrintValue("123m"), 123);
  EXPECT_EQ(PrintValue("123M"), 123);
  EXPECT_EQ(PrintValue("2147483647"), 2147483647);
  EXPECT_EQ(PrintValue("2147483647M"), 2147483647);
  EXPECT_EQ(PrintValue("2147483647m"), 2147483647);
}


// Demonstrate some basic assertions.
// TEST(HelloTestSuite, HelloTest) {
//   // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
//   // Expect equality.
//   EXPECT_EQ(7 * 6, 42);
// }

// // Testing with function from different file
// // Tests factorial of 0.
// TEST(FactorialTest, HandlesZeroInput) {
//   EXPECT_EQ(Factorial(0), 1);
// }

// // Tests factorial of positive numbers.
// TEST(FactorialTest, HandlesPositiveInput) {
//   EXPECT_EQ(Factorial(1), 1);
//   EXPECT_EQ(Factorial(2), 2);
//   EXPECT_EQ(Factorial(3), 6);
//   EXPECT_EQ(Factorial(8), 40320);
// }