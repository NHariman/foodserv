/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/27 14:45:09 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <fstream>
#include <iostream>

// default constructor
NginxConfig::NginxConfig() {} 

// constructor which holds the file name of the nginx config
NginxConfig::NginxConfig(std::ifstream& config_file) {
	// read line by line and fill the NginxConfig class
	std::cout << "lmao nailed it" << std::endl;
	
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


