/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 18:06:26 by nhariman      #+#    #+#                 */
/*   Updated: 2022/05/17 19:11:22 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "print_string.hpp"
#include <gtest/gtest.h>

// helpful links:
/*
    https://www.srcmake.com/home/google-cpp-test-framework //basic testing example and executing
    https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
    https://github.com/smistad/GTest/blob/master/CMakeLists.txt CMakeLists example
*/

// to get it working, install cmake and libgtest-dev
// sudo apt-get install libgtest-dev
// sudo apt-get install cmake

// then run 
//      cmake CMakeLists.txt
// then make to create the executable called runTests (found in the CMakeLists.txt file)

// every TEST is a group of tests you want to perform on a function
/* 
    TEST(functionName + Test, descriptive_type_of_test) {
        // whatever tests you want here
    }
*/
TEST(print_stringTest, incorrect) {
    // this works as a regular function so you can also define your own functions and variables within the test
    ASSERT_EQ(0, strcmp(print_string("hellohelp", "goodbye").c_str(), "hellogoodbye")); // if assert, will still try other tests
}

TEST(print_stringTest, correct) {
    EXPECT_EQ(0, strcmp(print_string("hello", "goodbye").c_str(), "hellogoodbye")); // if expect, will stop after failure
}

TEST(additionTest, correct) {
    int a = 10;
    int b = 5;
    EXPECT_EQ(a + b, addition(a, b));
    EXPECT_EQ(5 + 10, addition(a, b));
}

TEST(additionTest, incorrect) {
    int a = 10;
    int b = 5;
    EXPECT_NE(a + a, addition(a, b)); // not equal to
    EXPECT_NE(5 + 11, addition(a, b));
}


// in this case I wrote a function that combines two strings and returns it.
// strcmp is used to compare if the print_string output is identical to the expected output.
// if it is, it will equal to 0 and pass the test. (EXPECT_EQ)

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // will just always run all tests
}
