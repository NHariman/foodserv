#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
#include "../../src/request/request.hpp"
#include "../../src/resolved_target/target_config.hpp"
# include <map>
#include <string>
#include <vector>
#include <iostream>

// Test syntax
/*
		TEST(TestSuiteName, TestName) {
		... test body ...
		}
*/

TEST(TargetConfigTests, valid) {
	NginxConfig input("config_files/default.conf");

	TargetConfig def;
	TargetConfig test;
	TargetConfig test_two;
	TargetConfig cgi_bin;

	def.Setup(&input, "localhost", "80", "/");
	test.Setup(&input, "localhost", "80", "/test");
	test_two.Setup(&input, "localhost", "80", "/test_two");
	cgi_bin.Setup(&input, "localhost", "80", "/cgi-bin/");
	// testing default location "/"
	EXPECT_TRUE(	def.GetAutoindex());
	EXPECT_EQ(		def.GetRoot(), "/a_place");
	EXPECT_FALSE(	def.IsAllowedMethod("GET"));
	EXPECT_TRUE(	def.IsAllowedMethod("POST"));
	EXPECT_FALSE(	def.IsAllowedMethod("DELETE"));
	EXPECT_EQ(		def.GetClientMaxBodySize(), 5);
	// testing /test
	EXPECT_FALSE(	test.GetAutoindex());
	EXPECT_FALSE(	test.IsAllowedMethod("GET"));
	EXPECT_FALSE(	test.IsAllowedMethod("POST"));
	EXPECT_FALSE(	test.IsAllowedMethod("DELETE"));
	EXPECT_EQ(		test.GetClientMaxBodySize(), 64);
	
	// testing /test_two
	EXPECT_EQ(		test_two.GetRoot(), "/var/www/html");	
	EXPECT_FALSE(	test_two.IsAllowedMethod("GET"));
	EXPECT_FALSE(	test_two.IsAllowedMethod("POST"));
	EXPECT_FALSE(	test_two.IsAllowedMethod("DELETE"));
	EXPECT_EQ(		test_two.GetClientMaxBodySize(), 64);
	// testing /cgi-bin/
	EXPECT_EQ(		cgi_bin.GetRoot(), "/");	
	EXPECT_TRUE(	cgi_bin.IsAllowedMethod("GET"));
	EXPECT_TRUE(	cgi_bin.IsAllowedMethod("POST"));
	EXPECT_TRUE(	cgi_bin.IsAllowedMethod("DELETE"));
	EXPECT_EQ(		cgi_bin.GetClientMaxBodySize(), 64);
}
