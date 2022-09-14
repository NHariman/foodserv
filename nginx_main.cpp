/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/09/14 17:25:09 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		target.Setup(&input_file, "localhost", "80", "/test");
		// test ook : /test2/meer
	
		// std::cout << std::boolalpha << "Allowed method: GET: " << target.IsAllowedMethod("GET") << std::endl;
		// std::cout << std::boolalpha << "Allowed method: POST: " << target.IsAllowedMethod("POST") << std::endl;
		// std::cout << std::boolalpha << "Allowed method: DELETE: " << target.IsAllowedMethod("DELETE") << std::endl;
		// std::cout << "Get max body size: " << target.GetMaxBodySize() << std::endl;
		// std::cout << "Get Alias: " << target.GetAlias() << std::endl;


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
