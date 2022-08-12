/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/08/12 15:41:00 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/config/server_selection.hpp"
#include "src/config/setup.hpp"

int	main(int ac, const char **av) {
	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
		std:: cout << "try to get CMBS: " << std::endl;
		std:: cout << "CMBS in location WITH one set" << \
		input_file.GetServers().at(0).GetLocationContexts().at(0).GetClientMaxBodySize() << std::endl;
		std::cout << "CMBS in location WITHOUT one set" << \
		input_file.GetServers().at(0).GetLocationContexts().at(1).GetClientMaxBodySize() << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}