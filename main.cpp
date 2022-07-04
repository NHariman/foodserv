/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/04 13:33:35 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include "config/nginx_config.hpp"

int main(int ac, const char **av)
{
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	NginxConfig		configuration;
	std::ifstream	config_file_location;
	if (!av[1]) {
		av[1] = "config/default.conf";
		std::cerr << ">> WARNING! No config file given, config/default.conf used." << std::endl;
	}
	config_file_location.open(av[1]);

	if (config_file_location.is_open())
		configuration.ParseConfigFile(config_file_location);
	else {
		std::cerr << ">> ERROR! Unable to open: " << av[1] << std::endl;
		return 1; // error code change
	}
	config_file_location.close();
	return (0);
}
