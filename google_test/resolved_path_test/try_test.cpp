#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/resolved_target/target_config.hpp"

TEST(ReturnTest, ResolvedPathTesting) {

	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/test_config/return.conf");
	TargetConfig	target;

{
	target.Setup(&test, "localhost", "80", "/");
	EXPECT_EQ(target.GetResolvedPath(), "/test/deze/shit");
}
{
	target.Setup(&test, "localhost", "100", "/");
	EXPECT_EQ(target.GetResolvedPath(), "/helemaal/onder");
}
{
	target.Setup(&test, "localhost", "100", "/");
	EXPECT_EQ(target.GetResolvedPath(), "/helemaal/onder");
}
{
	target.Setup(&test, "localhost", "8080", "/test");
	EXPECT_EQ(target.GetResolvedPath(), "/test/return/in/location");

}
}

