#include <gtest/gtest.h>
#include "../../src/config/key_validation/autoindex.hpp"

int Factorial(int n);

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

TEST(AutoIndexTest, ValidInput) {
  EXPECT_NO_THROW({
    Autoindex test("on");
  });
  EXPECT_NO_THROW({
    Autoindex test("off");
  });
}

TEST(AutoIndexTest, invalidInput) {
  EXPECT_THROW({
    Autoindex test("onf");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("offe");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("1");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("off e");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("on e");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("k on");
  }, Autoindex::InvalidAutoindexException);
  EXPECT_THROW({
    Autoindex test("oh off");
  }, Autoindex::InvalidAutoindexException);
}