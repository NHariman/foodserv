#include <gtest/gtest.h>
#include "../../src/config/key_validation/root.hpp"

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/


TEST(RootTest, InvalidInput) {
  EXPECT_THROW({
    Root test("");
  }, Root::MissingArgumentsException);

}
