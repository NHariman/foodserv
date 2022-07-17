#include <gtest/gtest.h>
#include "../../src/config/key_validation/allowed_methods.hpp"

int Factorial(int n);

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

TEST(AllowedMethodsTest, ValidInput) {
  EXPECT_NO_THROW({
    AllowedMethods test("GET");
  });
  EXPECT_NO_THROW({
    AllowedMethods test("POST");
  });
  EXPECT_NO_THROW({
    AllowedMethods test("DELETE");
  });
  EXPECT_NO_THROW({
    AllowedMethods test("GET DELETE");
  });
  EXPECT_NO_THROW({
    AllowedMethods test("GET POST DELETE");
  });
}

TEST(AllowedMethodsTest, InvalidInput) {
  EXPECT_THROW({
    AllowedMethods test("GETP");
  }, AllowedMethods::BadMethodException);
  EXPECT_THROW({
    AllowedMethods test("POSTS");
  }, AllowedMethods::BadMethodException);
  EXPECT_THROW({
    AllowedMethods test("DELETEE");
  }, AllowedMethods::BadMethodException);
  EXPECT_THROW({
    AllowedMethods test("GET DFD DELETE");
  }, AllowedMethods::BadMethodException);
  EXPECT_THROW({
    AllowedMethods test("GET POST DELETE BB");
  }, AllowedMethods::BadMethodException);
  EXPECT_THROW({
    AllowedMethods test("GETPOST DELETE BB");
  }, AllowedMethods::BadMethodException);
}
