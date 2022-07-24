#include <gtest/gtest.h>
#include "../../src/config/directive_validation/fastcgi_pass.hpp"

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/


TEST(ErrorPageTest, InvalidInput) {
  EXPECT_THROW({
    FastCGIPass test("");
  }, FastCGIPass::MissingArgumentsException);

}
