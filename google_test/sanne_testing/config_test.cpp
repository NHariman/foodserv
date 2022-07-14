#include <gtest/gtest.h>

// run: cmake -S . -B build
// run: cmake --build build
// run: cd build
// run: ctest

// if test is changed run the last 3 commands again.
// make sure to be in the correct testing directory

TEST(ConfigTest, BasicAssertions) {
    EXPECT_STRNE("hello", "bye") << "add a message to the test like this.";
    EXPECT_EQ(7 * 6, 42);
}