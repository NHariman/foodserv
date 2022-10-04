#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

static NginxConfig config("../default.conf");

TEST(ConnectionTest, CheckErrorDispatch) {
	Connection connection(42, &config);

	connection.Receive("GET //thisisabadpath HTTP/1.1\r\nHost: localhost\n\n");
	connection.Dispatch();
}
