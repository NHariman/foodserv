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


TEST(RootTest, ResolvedPathTesting) {
	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/test_config/root.conf");
	TargetConfig	target;
{
	target.Setup(&test, "localhost", "80", "/hoi");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/HTML/hoi");
}
{
	target.Setup(&test, "localhost", "80", "/hoi/otherroot");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/hoi/otherroot");
}
{
	target.Setup(&test, "localhost", "80", "/doei/he");
	EXPECT_EQ(target.GetResolvedPath(), "/Crap/doei");
}
{
	target.Setup(&test, "localhost", "80", "/moreslashes");
	EXPECT_EQ(target.GetResolvedPath(), "/Slash/queen/moreslashes");
}
{
	target.Setup(&test, "localhost", "80", "/dir/more");
	EXPECT_EQ(target.GetResolvedPath(), "");
}
{
	target.Setup(&test, "localhost", "80", "/auto/on/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/HTML/otherpage.html");
}
{
	target.Setup(&test, "localhost", "8080", "/auto/on/");
	EXPECT_EQ(target.GetResolvedPath(), "");
}
{
	target.Setup(&test, "localhost", "8888", "/auto/on/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/HTML/index.html");
}
}

TEST(AlisTest, ResolvedPathTesting) {
	
}