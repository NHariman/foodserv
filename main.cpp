#include <iostream>
#include <string>
#include <fstream>
#include "config/nginx_config.hpp"

int main(int ac, char **av)
{
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	std::ifstream config_file_location;
	if (!av[1]) {
		av[1] = "config/default.conf";
		// throw error? OR because presistence is key, automatically default to a basic config file
	}
	config_file_location.open(av[1]);
	if (config_file_location.is_open())
		NginxConfig nginx_config(config_file_location);
	else
	{
		config_file_location.open("config/default.conf");
		NginxConfig nginx_config(config_file_location);
		if (config_file_location.is_open())
			NginxConfig nginx_config(config_file_location);
		else
		{
			std::cerr << "No config file provided and Default config file missing, cannot create server" << std::endl;
			return 1;
		}
		//load in default config file and parse
	}
	// do other stuff
	return (0);
}
