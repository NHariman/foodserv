#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/resolved_target/target_config.hpp"

using namespace std;


TEST(RootTest, RootTest) {
	NginxConfig	test("/Users/sannealbreghs/Desktop/foodserv/test_config/root.conf");

	TargetConfig	target;

	target.Setup(&test, "localhost", "80", "/");

		
}