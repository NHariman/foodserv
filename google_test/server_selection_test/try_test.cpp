#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
#include "../../src/config/server_selection.hpp"

// Create a function to check if the config vectors are as expected

TEST(TestFake, Test) {
    NginxConfig	test1("/Users/sannealbreghs/Desktop/foodserv/test_config/conf1.conf"); // send conf1.conf

	ServerSelection	server_context_selection("localhost", "80", test1.GetServers());
    EXPECT_EQ(0,0);
}