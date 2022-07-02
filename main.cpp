/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/02 16:18:23 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include "config/nginx_config.hpp"

int main(int ac, char **av)
{
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	NginxConfig configuration;
	std::ifstream config_file_location;
	if (!av[1]) {
		av[1] = "config/default.conf";
		std::cerr << ">> WARNING! No config file given, config/default.conf used." << std::endl;
		// throw error? OR because presistence is key, automatically default to a basic config file
	}
	config_file_location.open(av[1]);
	if (config_file_location.is_open())
		configuration.ParseConfigFile(config_file_location);
	else
	{
		config_file_location.open("config/default.conf");
		if (config_file_location.is_open())
			configuration.ParseConfigFile(config_file_location);
		else
		{
			std::cerr << ">> WARNING! No config file provided and Default config file missing, cannot create server." << std::endl;
			return 1;
		}
		//load in default config file and parse
	}
	config_file_location.close();
	// do other stuff
	return (0);
}
