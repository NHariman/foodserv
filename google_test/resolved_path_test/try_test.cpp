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
	resolved_path.Resolve(request.GetTargetString(), request.GetMethod());
	EXPECT_EQ(resolved_path.GetResolvedPath(), "/test/deze/shit");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "100", "/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), request.GetMethod());
	EXPECT_EQ(resolved_path.GetResolvedPath(), "/helemaal/onder");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "100", "/niks");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "/helemaal/onder");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/hoi");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "/test/return/in/location");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "/test/return/in/location");
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
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "80", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/coffee_and_beans/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/index.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "8080", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/coffee_and_beans/index.html");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "test_second", "8080", "/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/otherpage.html");
}
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "test_second", "8080", "/coffee_and_beans/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/coffee_and_beans/otherpage.html");
}

{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "666", "/");
	ResolvedPath	resolved_path(&target);
	resolved_path.Resolve(request.GetTargetString(), "GET");
	EXPECT_EQ(resolved_path.GetResolvedPath(), "../www/html/");
}
}


TEST (AutoIndex, ResolvedPathTesting) {
	NginxConfig		test("../config_files/root.conf");
	Request	request(&test);
{
	TargetConfig target = request.GetTargetConfig();
	target.Setup(&test, "localhost", "666", "/");
	EXPECT_EQ(target.GetResolvedPath(), "");
	EXPECT_EQ(target.MustGenerateIndex(), true);
}

// }
// // {
// // 	target.Setup(&test, "localhost", "8080", "/auto/on/");
// // 	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/auto/on/");
// // 	EXPECT_EQ(target.MustGenerateIndex(), true);
// // }
// // {
// // 	target.Setup(&test, "localhost", "666", "/HTML/");
// // 	EXPECT_EQ(target.GetResolvedPath(), "/Users/sannealbreghs/Desktop/foodserv/www/html/otherpage.html");
// // 	EXPECT_EQ(target.MustGenerateIndex(), false);
// // }
}
