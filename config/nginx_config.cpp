/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/28 17:02:18 by nhariman      ########   odam.nl         */
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
	while(std::getline(config_file, tp))
	{
		// this structure is SO wrong but it's a first draft
		size_t found = tp.find("http{");
		if (found == std::string::npos)
		{
			std::cerr << "[ERROR] No http block found." << std::endl;
			return ; // maybe throw??
		}
		found = tp.find("client_max_body_size ", found + 1);
		if (found == std::string::npos)
		{
			std::cerr << "[WARNING] No global client max body size set. Default has been set (1mb)" << std::endl;
			this->main_body_client_max_body_size = 1;
		}
		found = tp.find("access_log ", found + 1);
		if (found == std::string::npos)
		{
			std::cerr << "[WARNING] No access_log status set. Default has been set (on)" << std::endl;
			this->access_log = 1;
		}
		found = tp.find("error_page ", found + 1);
		if (found == std::string::npos)
		{
			std::cerr << "[WARNING] No error_page set. Defaults have been set" << std::endl;
			this->access_log = 1;
		}
		else
		{
			// set access_log
		}
		found = tp.find("server{", found + 1);
		if (found == std::string::npos)
		{
			// check if other servers have been set or not, if not print warning, otherwise just continue.
			std::cerr << "[WARNING] No servers set. Default has been set." << std::endl;
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


