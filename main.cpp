#include <iostream>
#include "src/config/nginx_config.hpp"

// not in use yet
int	main(int ac, const char **av) {
	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
