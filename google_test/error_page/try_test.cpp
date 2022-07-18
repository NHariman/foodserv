#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/config/key_validation/error_page.hpp"

// Test syntax
/*
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

TEST(ErrorPageTest, ValidInput) {
  EXPECT_NO_THROW({
    ErrorPage test("500 502 503 504 /50x.html");
  });
  EXPECT_NO_THROW({
    ErrorPage test("404             /404.html");
  });
  EXPECT_NO_THROW({
    ErrorPage test("404 /404.html");
  });
  EXPECT_NO_THROW({
    ErrorPage test("500 502 503 504 404 403 402 405 /50x.html");
  });
}

TEST(ErrorPageTest, InvalidInput) {
  EXPECT_THROW({
    ErrorPage test("404 /404.html 404");
  }, ErrorPage::InvalidInputException);
  EXPECT_THROW({
    ErrorPage test("404 404.html /stuff.html");
  }, ErrorPage::InvalidInputException);
  EXPECT_THROW({
    ErrorPage test("404 abc /404.html");
  }, ErrorPage::InvalidInputException);
  EXPECT_THROW({
    ErrorPage test("404d 404 /404.html");
  }, ErrorPage::InvalidInputException);
  EXPECT_THROW({
    ErrorPage test("404 404.html");
  }, ErrorPage::InvalidInputException);
  EXPECT_THROW({
    ErrorPage test("404 /404.html /404.html");
  }, ErrorPage::DuplicateUriException);
}
