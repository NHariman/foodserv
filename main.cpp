#include "src/config/nginx_config.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"

int	main(int ac, const char **av) {
	(void)ac;

	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
		
		TargetConfig target;
		target.Setup(&input_file, "localhost", "80", "/");
	
		std::cout << std::boolalpha << "Allowed method: GET: " << target.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target.IsAllowedMethod("DELETE") << std::endl;
		std::cout << "Get max body size: " << target.GetMaxBodySize() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);	
}
