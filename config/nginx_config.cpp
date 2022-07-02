/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/02 16:28:27 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <fstream>
#include <iostream>
#include <string>

// clang++ main.cpp config/server_block.cpp config/location_block.cpp config/nginx_config.cpp

// default constructor that sets all the defaults, these are later overwritten by actual configuration stuff
NginxConfig::NginxConfig() 
{
	components.error_page = false;
	components.access_log = false;
	components.client_max_body_size = false;
	components.server_block = 0;
	http_client_max_body_size = 1;
	access_log = false; // maybe remove for simplicity's sake?
	// TODO:
	// make a default server block to insert into the vector
	// make a default error page to insert into the map
}

// parses the received config file to overwrite defaults
int		NginxConfig::ParseConfigFile(std::ifstream& config_file)
{
	// move to a new function, the defauconstructor only sets defaults.
	// maybe this only sets the defaults and actual parsing occurs later?
	// read line by line and fill the NginxConfig class
	std::string tp;
	std::string content;
	size_t		found;
	while(std::getline(config_file, tp))
	{
		content.append(tp + "\n");
		found = tp.find("http{");
		if (found != std::string::npos)
			break ;
		else if (config_file.eof())
		{
			std::cerr << "[ERROR] No http block found." << std::endl;
			return ;
		}
	}
	while(std::getline(config_file, tp))
	{
		//content.append(tp + "\n");
		if (tp.find("#") != std::string::npos) // deletes any comments found in the line
			tp.erase(tp.find("#"));
		// TODO:
		// add exit condition if } is found for the http block
		found = std::string::npos;
		if ((found = tp.find("client_max_body_size ")) != std::string::npos)
		{
			components.client_max_body_size = true;
			// TODO:
			// add parser that finds the client max body size number and saves it.
			std::cout << "client_max_body_size identified" << std::endl;
		}
		else if ((found = tp.find("access_log ")) != std::string::npos)
		{
			components.access_log = true;
			// TODO:
			// add parser that finds the access_log identifier (true/false) and saves it.
			std::cout << "access_log identified" << std::endl;
		}
		else if ((found = tp.find("error_page ")) != std::string::npos)
		{
			components.error_page = true;
			// TODO:
			// add parser that gets the error_page data and saves it.
			std::cout << "error_page identified" << std::endl;
		}
		else if ((found = tp.find("server{")) != std::string::npos)
		{
						// TODO:
			// this should call the serverblock class which works similarly to the NginxConfig class
			// it first sets some defaults
			// then parses from server{ to }
			std::cout << "server_block identified" << std::endl;
			components.server_block++;
		}
		content.append(tp + "\n");
	}
	std::cout << content << std::endl;
	ComponentChecker(components);
}

// checks which components have been found in the http block
void	NginxConfig::ComponentChecker(s_components component)
{
	if (component.error_page == false)
		std::cerr << "[WARNING] No error_page set in http{}. Defaults have been set" << std::endl;
	if (component.access_log == false) 
		std::cerr << "[WARNING] No access_log set in http{}. Defaults have been set" << std::endl;
	if (component.client_max_body_size == false)
		std::cerr << "[WARNING] No global client max body size set in http{}. Default has been set (1mb)" << std::endl;
	if (component.server_block == 0)
		std::cerr << "[WARNING] No servers set. Default has been set." << std::endl;
}
