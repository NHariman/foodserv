#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/resolved_target/server_selection.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"

int	main(int ac, const char **av) {
	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
		
		TargetConfig target;
		TargetConfig target_test;
		TargetConfig target_test_two;
		TargetConfig target_cgi_bin;
		TargetConfig target_cgi_bin_two;
		target.Setup(&input_file, "localhost", "80", "/");
		target_test.Setup(&input_file, "localhost", "80", "/test");
		target_test_two.Setup(&input_file, "localhost", "80", "/test_two");
		target_cgi_bin.Setup(&input_file, "localhost", "80", "/cgi-bin/");
		target_cgi_bin_two.Setup(&input_file, "localhost", "80", "/cgi-bin1/");
	

		std::cout << "*****FOR LOCATION: / ******" << std::endl;

		std::cout << "location URI: " << target.GetLocationUri().GetInputURI() << std::endl;
		std::cout <<  "is directory? " << std::boolalpha << target.GetLocationUri().IsDir() << std::endl;
		std::cout << "root: " << target.GetRoot() << std::endl;
		std::cout << "index: ";
		for (size_t i = 0; i < target.GetIndex().size(); i++)
   			std::cout << target.GetIndex().at(i) << ' ';
		std::cout << std::endl;
		std::cout << "Get max body size: " << target.GetMaxBodySize() << std::endl;
		std::cout << "Print error_page: " << std::endl;
		target.PrintErrorPage();
		std::cout << "Get autoindex: " << std::boolalpha << target.GetAutoindex() << std::endl;
		for (size_t i = 0; i < target.GetAllowedMethods().size(); i++)
   			std::cout << target.GetAllowedMethods().at(i) << ' ';
		std::cout << std::boolalpha << "Allowed method: GET: " << target.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target.IsAllowedMethod("DELETE") << std::endl;
		std::cout << target.GetReturn() << std::endl;
		std::cout << "cgi_pass: " << target.GetCGIPass() << std::endl;
		std::cout << "alias: " << target.GetAlias() << std::endl;
		std::cout << "resolved path: " << target.GetResolvedPath() << std::endl;

		std::cout << "\n*****FOR LOCATION: /test ******" << std::endl;
		std::cout << "location URI: " << target_test.GetLocationUri().GetInputURI() << std::endl;
		std::cout << "is directory? " << target_test.GetLocationUri().IsDir() << std::endl;
		std::cout << "root: " << target_test.GetRoot() << std::endl;
		std::cout << "index: ";
		for (size_t i = 0; i < target_test.GetIndex().size(); i++)
   			std::cout << target_test.GetIndex().at(i) << ' ';
		std::cout << std::endl;
		std::cout << "Get max body size: " << target_test.GetMaxBodySize() << std::endl;
		std::cout << "Print error_page: " << std::endl;
		target_test.PrintErrorPage();
		std::cout << "Get autoindex: " << std::boolalpha << target_test.GetAutoindex() << std::endl;
		std::cout << std::boolalpha << "Allowed method: GET: " << target_test.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target_test.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target_test.IsAllowedMethod("DELETE") << std::endl;
		std::cout << target_test.GetReturn() << std::endl;
		std::cout << "cgi_pass: " << target_test.GetCGIPass() << std::endl;
		std::cout << "alias: " << target_test.GetAlias() << std::endl;
		std::cout << "resolved path: " << target_test.GetResolvedPath() << std::endl;


		std::cout << "\n*****FOR LOCATION: /test_two ******" << std::endl;
		std::cout << "location URI: " << target_test_two.GetLocationUri().GetInputURI() << std::endl;
		std::cout << "is directory? " << target_test_two.GetLocationUri().IsDir() << std::endl;
		std::cout << "root: " << target_test_two.GetRoot() << std::endl;
		std::cout << "index: ";
		for (size_t i = 0; i < target_test_two.GetIndex().size(); i++)
   			std::cout << target_test_two.GetIndex().at(i) << ' ';
		std::cout << std::endl;
		std::cout << "Get max body size: " << target_test_two.GetMaxBodySize() << std::endl;
		std::cout << "Print error_page: " << std::endl;
		target_test_two.PrintErrorPage();
		std::cout << "Get autoindex: " << std::boolalpha << target_test_two.GetAutoindex() << std::endl;
		std::cout << std::boolalpha << "Allowed method: GET: " << target_test_two.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target_test_two.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target_test_two.IsAllowedMethod("DELETE") << std::endl;
		std::cout << target_test_two.GetReturn() << std::endl;
		std::cout << "cgi_pass: " << target_test_two.GetCGIPass() << std::endl;
		std::cout << "alias: " << target_test_two.GetAlias() << std::endl;
		std::cout << "resolved path: " << target_test_two.GetResolvedPath() << std::endl;


		std::cout << "\n*****FOR LOCATION: /cgi-bin ******" << std::endl;
		std::cout << "location URI: " << target_cgi_bin.GetLocationUri().GetInputURI() << std::endl;
		std::cout << "is directory? " << target_cgi_bin.GetLocationUri().IsDir() << std::endl;
		std::cout << "root: " << target_cgi_bin.GetRoot() << std::endl;
		std::cout << "index: ";
		for (size_t i = 0; i < target_cgi_bin.GetIndex().size(); i++)
   			std::cout << target_cgi_bin.GetIndex().at(i) << ' ';
		std::cout << std::endl;
		std::cout << "Get max body size: " << target_cgi_bin.GetMaxBodySize() << std::endl;
		std::cout << "Print error_page: " << std::endl;
		target_cgi_bin.PrintErrorPage();
		std::cout << "Get autoindex: " << std::boolalpha << target_cgi_bin.GetAutoindex() << std::endl;
<<<<<<< HEAD
=======
		std::cout << "Print allowed_methods vector: " << std::endl;
		for (size_t i = 0; i < target_cgi_bin.GetAllowedMethods().size(); i++)
   			std::cout << target_cgi_bin.GetAllowedMethods().at(i) << ' ';
>>>>>>> 9027679aaebb809973f841bcd44de52ab4be6b42
		std::cout << std::boolalpha << "Allowed method: GET: " << target_cgi_bin.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target_cgi_bin.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target_cgi_bin.IsAllowedMethod("DELETE") << std::endl;
		std::cout << target_cgi_bin.GetReturn() << std::endl;
		std::cout << "cgi_pass: " << target_cgi_bin.GetCGIPass() << std::endl;
		std::cout << "alias: " << target_cgi_bin.GetAlias() << std::endl;
		std::cout << "resolved path: " << target_cgi_bin.GetResolvedPath() << std::endl;




		std::cout << "\n*****FOR LOCATION: /cgi-bin1 ******" << std::endl;
		std::cout << "location URI: " << target_cgi_bin_two.GetLocationUri().GetInputURI() << std::endl;
		std::cout << "is directory? " << target_cgi_bin_two.GetLocationUri().IsDir() << std::endl;
		std::cout << "root: " << target_cgi_bin_two.GetRoot() << std::endl;
		std::cout << "index: ";
		for (size_t i = 0; i < target_cgi_bin_two.GetIndex().size(); i++)
   			std::cout << target_cgi_bin_two.GetIndex().at(i) << ' ';
		std::cout << std::endl;
		std::cout << "Get max body size: " << target_cgi_bin_two.GetMaxBodySize() << std::endl;
		std::cout << "Print error_page: " << std::endl;
		target_cgi_bin_two.PrintErrorPage();
		std::cout << "Get autoindex: " << std::boolalpha << target_cgi_bin_two.GetAutoindex() << std::endl;
		std::cout << std::boolalpha << "Allowed method: GET: " << target_cgi_bin_two.IsAllowedMethod("GET") << std::endl;
		std::cout << std::boolalpha << "Allowed method: POST: " << target_cgi_bin_two.IsAllowedMethod("POST") << std::endl;
		std::cout << std::boolalpha << "Allowed method: DELETE: " << target_cgi_bin_two.IsAllowedMethod("DELETE") << std::endl;
		std::cout << target_cgi_bin_two.GetReturn() << std::endl;
		std::cout << "cgi_pass: " << target_cgi_bin_two.GetCGIPass() << std::endl;
		std::cout << "alias: " << target_cgi_bin_two.GetAlias() << std::endl;
		std::cout << "resolved path: " << target_cgi_bin_two.GetResolvedPath() << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}

// int	main(int ac, const char **av) {
// 	try {
// 		NginxConfig input_file(GetConfigLocation(ac, av));
// 		std::cout << "try to get CMBS: " << std::endl;
// 		// std::cout << "CMBS in location WITH one set\n" << \
// 		// input_file.GetServers().at(0).GetLocationContexts().at(0).GetClientMaxBodySize() << std::endl;
// 		// try {
// 		// 	std::cout << "CMBS in location WITHOUT one set " << \
// 		// 	input_file.GetServers().at(0).GetLocationContexts().at(1).GetClientMaxBodySize() << std::endl;
// 		// }
// 		// catch (const std::exception& e) {
// 		// 	std::cerr << e.what() << "\n";
// 		// }
// 		std::cout << "now from NginxConfig" << std::endl;
// 		std::cout << "CMBS in location WITH one set VIA nginxconf ";
// 		std::cout << input_file.GetMaxBodySize("localhost", "/") << std::endl;
// 		// std::cout << "CMBS in location WITHOUT one set VIA nginxconf " << \
// 		// input_file.GetMaxBodySize("localhost", "/test") << std::endl;
// 		// std::cout << "Get GET" << std::endl;
// 		// std::cout << std::boolalpha << input_file.IsAllowedMethod("localhost", "/", "GET") << std::endl;
// 		// std::cout << "testing fastcgi_pass\n";
// 		// std::cout << input_file.GetCGIPass("localhost", "/cgi-bin") << std::endl;
// 		// std::cout << input_file.GetReturn("localhost", "/") << std::endl;
// 	}
// 	catch (const std::exception& e) {
// 		std::cerr << e.what() << '\n';
// 	}
// 	return (0);
// }
