// MAIN TO CHECK SERVER_SELECTION

#include <exception>

#include "src/config/nginx_config.hpp"
#include "src/config/server_selection.hpp"

int	main() {
	
	try {
		NginxConfig	conf("test_config/conf1.conf");

		ServerSelection		test1("localhost", "80", conf.GetServers());
		test1.PrintContextVectors();
	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		NginxConfig	conf("test_config/conf2.conf");

		ServerSelection		test("localhost", "80", conf.GetServers());
		test.PrintContextVectors();
	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}


}