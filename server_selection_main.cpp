// MAIN TO CHECK SERVER_SELECTION

#include <exception>

#include "src/config/nginx_config.hpp"
#include "src/config/server_selection.hpp"

void	compare_server_selection() {

}

int	main() {
		try {
		// SHOULD GRAB BLOK 80
		NginxConfig	conf("test_config/conf1.conf");

		ServerSelection		test1("localhost", "80", conf.GetServers());
		test1.PrintChosenServerblock();

	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		// SHOULD GRAB BLOK 80
		NginxConfig 	conf("test_config/conf1.conf");
		ServerSelection	test("", "80", conf.GetServers());
		test.PrintChosenServerblock();

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		// SHOULD GRAB BLOK 8080
		NginxConfig 	conf("test_config/conf1.conf");
		ServerSelection	test("something", "8080", conf.GetServers());
		test.PrintChosenServerblock();

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		// SHOULD GRAB 8080
		NginxConfig 	conf("test_config/conf1.conf");
		ServerSelection	test("", "8080", conf.GetServers());
		if (test.GetChosenServerContext().GetServerNameVector().size() == 0)
		test.PrintChosenServerblock();

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		// SHOULD GRAB 80
		NginxConfig 	conf("test_config/conf1.conf");
		ServerSelection	test("", "1", conf.GetServers());
		test.PrintChosenServerblock();

	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// try {
	// 	NginxConfig	conf("test_config/conf2.conf");

	// 	ServerSelection		test("localhost", "80", conf.GetServers());
	// 	test.PrintChosenServerblock();
	// } catch(const std::exception& e) {
	// 	std::cerr << e.what() << std::endl;
	// }


}