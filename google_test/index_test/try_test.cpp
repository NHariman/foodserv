#include <gtest/gtest.h>
#include "../../src/config/key_validation/index.hpp"

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

// TEST(ErrorPageTest, ValidInput) {
//   EXPECT_NO_THROW({
//     ErrorPage test("500 502 503 504 /50x.html");
//   });
//   EXPECT_NO_THROW({
//     ErrorPage test("404             /404.html");
//   });
//   EXPECT_NO_THROW({
//     ErrorPage test("404 /404.html");
//   });
//   EXPECT_NO_THROW({
//     ErrorPage test("500 502 503 504 404 403 402 405 /50x.html");
//   });
// }

TEST(IndexTest, InvalidInput) {
  EXPECT_THROW({
    Index test("");
  }, Index::MissingArgumentsException);
  
}
