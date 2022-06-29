/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/29 18:17:17 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <fstream>
#include <iostream>
#include <string>

// default constructor
NginxConfig::NginxConfig() {} 

// constructor which holds the file name of the nginx config
NginxConfig::NginxConfig(std::ifstream& config_file) {
	// maybe this only sets the defaults and actual parsing occurs later?
	// read line by line and fill the NginxConfig class
	std::cout << "lmao nailed it" << std::endl;
	std::string tp;
	std::string content;
	size_t		found;
	while(std::getline(config_file, tp))
	{
		found = tp.find("http{");
		if (found)
			break ;
		else if (config_file.eof())
		{
			std::cerr << "[ERROR] No http block found." << std::endl;
			return ;
		}
	}
	while(std::getline(config_file, tp))
	{
		found = 0;
		// this structure is SO wrong but it's a first draft
		found = tp.find("client_max_body_size ");
		if (found)
		{
			components.client_max_body_size = true;
			std::cout << "client_max_body_size identified" << std::endl;
			// move to error
			// std::cerr << "[WARNING] No global client max body size set. Default has been set (1mb)" << std::endl;
			// this->main_body_client_max_body_size = 1;
		}
		found = 0;
		found = tp.find("access_log ");
		if (found)
		{
			components.access_log = true;
			std::cout << "access_log identified" << std::endl;
			// move to error
			// std::cerr << "[WARNING] No access_log status set. Default has been set (on)" << std::endl;
			// this->access_log = 1;
		}
		found = tp.find("error_page ");
		if (found)
		{
			components.error_page = true;
			std::cout << "error_page identified" << std::endl;
			// std::cerr << "[WARNING] No error_page set. Defaults have been set" << std::endl;
			// this->access_log = 1;
		}
		found = tp.find("server{");
		if (found)
		{
			std::cout << "server_block identified" << std::endl;
			components.server_block++;
			// initiate the serverblock constructor
			// check if other servers have been set or not, if not print warning, otherwise just continue.
			//std::cerr << "[WARNING] No servers set. Default has been set." << std::endl;
		}
		// enter http parsing block
		// look for server blocks, client_max_body_siz, error_log
		// if server block, initialise server block in vector
		content.append(tp + "\n");
	}
	std::cout << content << std::endl;
	// this part in main?
	// step 1. check if string is not empty
	// std::ifstream config;
	// if (!config_file) {
	// 	// throw error? OR because presistence is key, automatically default to a basic config file
	// }
	// config.open(config_file);
	// if (config.is_open())
	// 	// parse config file
	// else
	// {
	// 	//load in default config file and parse
	// }
	// step 2. check if string is an actual config file by trying to open it
	// step 3. start parsing the config file
}

void	NginxConfig::loadConfigMap() {}


