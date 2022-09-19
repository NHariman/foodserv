#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/resolved_target/server_selection.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"

int	main(int ac, const char **av) {
	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
		
		TargetConfig target;
		target.Setup(&input_file, "localhost", "80", "/html-pages/index.html");
	
		// std::cout << std::boolalpha << "Allowed method: GET: " << target.IsAllowedMethod("GET") << std::endl;
		// std::cout << std::boolalpha << "Allowed method: POST: " << target.IsAllowedMethod("POST") << std::endl;
		// std::cout << std::boolalpha << "Allowed method: DELETE: " << target.IsAllowedMethod("DELETE") << std::endl;
		// std::cout << "Get max body size: " << target.GetMaxBodySize() << std::endl;
		// std::cout << "Get autoindex: " << std::boolalpha << target.GetAutoindex() << std::endl;
		// std::cout << "Print error_page: " << std::endl;
		// target.PrintErrorPage();

		std::cout << "PATH: " << target.GetResolvedPath() << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}