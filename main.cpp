/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/09/07 17:42:15 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/server_selection/server_selection.hpp"

int	main(int ac, const char **av) {
	(void)ac;
	try {
		NginxConfig		input_file(av[1]);

		ServerSelection	serverblock_selection("localhost", "80", input_file.GetServers());
		// add exceptions in the server_selection class to make it able to throw.
		std::cout << "Amount of serverblocks: " << input_file.GetServerContextAmount() << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	// ServerSelection	chosen_serverblock(input_file.GetServers());
	// Server servie(80, INADDR_ANY);
	
	return (0);
}
