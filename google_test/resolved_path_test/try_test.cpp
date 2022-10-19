#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/resolved_target/target_config.hpp"
#include "../../src/request/request.hpp"

// RETURN TESTING
TEST(ReturnTest, ResolvedPathTesting) {

	NginxConfig		test("../config_files/return.conf");
	Request	request(&test);

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "80", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "/test/deze/shit");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "100", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "/helemaal/onder");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "100", "/niks");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/niks", "GET"), "/helemaal/onder");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/hoi");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/hoi", "GET"), "/test/return/in/location");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "/test/return/in/location");
}
}

// ROOT TESTING
TEST(RootTest, ResolvedPathTesting) {
	NginxConfig		test("../config_files/root.conf");
	Request	request(&test);

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "80", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "../www/html/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "80", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/coffee_and_beans/", "GET"), "../www/html/coffee_and_beans/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "../www/html/index.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/coffee_and_beans/", "GET"), "../www/html/coffee_and_beans/index.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "test_second", "8080", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "../www/html/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "test_second", "8080", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/coffee_and_beans/", "GET")
, "../www/html/coffee_and_beans/otherpage.html");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "666", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "../www/html/index.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "666", "/img/beans.png");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/img/beans.png", "GET"), "../www/img/beans.png");
}
}


TEST (AutoIndex, ResolvedPathTesting) {
	NginxConfig		test("../config_files/root.conf");
	Request	request(&test);
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "777", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "");
	EXPECT_EQ(target.MustGenerateIndex(), false);
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "777", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", "GET"), "");
	EXPECT_EQ(target.MustGenerateIndex(), false);
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "777", "/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/", ""), "../www/html/");
	EXPECT_EQ(target.MustGenerateIndex(), false);
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "test_2", "777", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	EXPECT_EQ(resolved_path.Resolve("/coffee_and_beans/", "GET"), "../www/html/coffee_and_beans/");
	EXPECT_EQ(target.MustGenerateIndex(), true);	
}
}
