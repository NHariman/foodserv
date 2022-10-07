#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/resolved_target/target_config.hpp"

TEST(ReturnTest, ResolvedPathTesting) {

	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/return.conf");
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
	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/root.conf");
	TargetConfig	target;
{
	target.Setup(&test, "localhost", "80", "/hoi");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/hoi");
}
{
	target.Setup(&test, "localhost", "80", "/hoi/otherroot");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/hoi/otherroot");
}
{
	target.Setup(&test, "localhost", "80", "/doei/he");
	EXPECT_EQ(target.GetResolvedPath(), "/Crap/doei/he");
}
{
	target.Setup(&test, "localhost", "80", "/moreslashes");
	EXPECT_EQ(target.GetResolvedPath(), "/Slash/queen/moreslashes");
}
{
	target.Setup(&test, "localhost", "80", "/dir/more");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/dir/more");
}
{
	target.Setup(&test, "localhost", "80", "/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/otherpage.html");
}
{
	target.Setup(&test, "localhost", "8888", "/Desktop/foodserv/www/html/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/index.html");
}
}

TEST(AliasTest, ResolvedPathTesting) {
	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/alias.conf");
	TargetConfig	target;

{
	target.Setup(&test, "localhost", "80", "/html-pages/index.html");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/index.html");
}
{
	target.Setup(&test, "localhost", "80", "/html-pages");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/index.html");
}
{
	target.Setup(&test, "test", "888", "/pages/");
	EXPECT_EQ(target.GetResolvedPath(), "");
}
{
	target.Setup(&test, "test", "888", "/test2/index.html");
	EXPECT_EQ(target.GetResolvedPath(), "/User/sannealbreghs/Desktop/foodserv/www/html/index.html");
}
{
	target.Setup(&test, "noname", "888", "/config_files/test_config/alias.conf");
	EXPECT_EQ(target.GetResolvedPath(), "/User/sannealbreghs/Desktop/foodserv/config_files/test_config/alias.conf");
}
}

TEST (AutoIndex, ResolvedPathTesting) {
	NginxConfig		test("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/root.conf");
	TargetConfig	target;
{
	target.Setup(&test, "local", "666", "/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/");
	EXPECT_EQ(target.MustGenerateIndex(), true);
}
{
	target.Setup(&test, "localhost", "8080", "/auto/on/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/auto/on/");
	EXPECT_EQ(target.MustGenerateIndex(), true);
}
{
	target.Setup(&test, "localhost", "666", "/HTML/");
	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/otherpage.html");
	EXPECT_EQ(target.MustGenerateIndex(), false);
}
}
