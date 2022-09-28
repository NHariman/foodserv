#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/resolved_target/server_selection.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"
#include "src/request/request.hpp"
#include "src/cgi/cgi.hpp"

int	main(int ac, const char **av) {
	try {
		(void)ac;
		(void)av;
		//NginxConfig config("config_files/CGI_test.conf");
		// NginxConfig config("config_files/cgi_testers/CGI_GET.conf");
		NginxConfig config("config_files/cgi_testers/CGI_POST.conf");
		
		Request request(&config);
		// request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");
		request.Parse("POST /cgi-bin/post_query.pl HTTP/1.1\r\nHost: localhost\n\n");
		std::cout << "Method: " << request.GetMethod() << std::endl;
		std::cout << "TargetString: " << request.GetTargetString() << std::endl;
		
		std::cout << "Target Config stuff:" << std::endl;
		std::cout << "Get resolved path: " << request.GetTargetConfig().GetResolvedPath() << std::endl;
		std::cout << "Get CGI path: " << request.GetTargetConfig().GetCGIPass() << std::endl;

		CGI cgi;
		cgi.setup(&request);
		int nb = cgi.execute();
		std::cout << "execute value: " << nb << std::endl;
		std::cout << "get content? " << std::endl;
		std::cout << cgi.getContent() << std::endl;
		// std::cout << "cgi setup status: " << std::boolalpha << cgi.setup(&request) << std::endl;
		// std::cout << "CGI execute status: " << std::endl;
		// size_t status = cgi.execute();
		// std::cout << "status: " << status << std::endl;
		// std::cout << "Contents? " << std::endl;
		// std::cout << cgi.getContent() << std::endl;
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
