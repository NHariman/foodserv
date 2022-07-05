/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/05 18:17:13 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "config/nginx_config.hpp"
#include "config/server_block.hpp"

int main(int ac, const char **av)
{
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	
	std::ifstream	config_file_fd;
	NginxConfig		input_file;
	if (!av[1]) {
		av[1] = "config/default.conf";
		std::cerr << ">> WARNING! No config file given, config/default.conf used." << std::endl;
	}
	config_file_fd.open(av[1]);
	if (config_file_fd.is_open()) {
		input_file.LoadConfigFile(config_file_fd);
		// try {
		// 	NginxConfig		input_file(config_file_fd);
		// }
		// catch (const std::invalid_argument& ia) {
		// 	std::cerr << "ERROR! " << ia.what() << '\n';
		// 	return 1;
		// }
	}
	else {
		std::cerr << ">> ERROR! Unable to open: " << av[1] << std::endl;
		return 1; // error code change
	}
	config_file_fd.close();
	if (input_file.FindServerBlocks() == 0){
		std::cerr << "ERROR! No server blocks found." << std::endl;
		return 1;
	}
	std::cout << "Amount of serverblocks: " << input_file.GetServerBlockAmount() << std::endl;
	return (0);
}
