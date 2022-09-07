/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/09/07 18:07:23 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/config/setup.hpp"
// #include "src/server_selection/server_selection.hpp"
#include "src/server_selection/target_config.hpp"

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
	
	// ServerSelection	chosen_serverblock(input_file.GetServers());
	// Server servie(80, INADDR_ANY);
	
	return (0);
}
