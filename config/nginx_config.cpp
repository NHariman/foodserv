/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 18:40:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/04 18:54:29 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"

NginxConfig::NginxConfig(std::ifstream configuration_file) {
	std::string	current_string;
	size_t		found;
	
	while(std::getline(configuration_file, current_string)) {
		if (config_string.find("#") != std::string::npos) // deletes any comments found in the line
			config_string.erase(config_string.find("#"));
	}
}

NginxConfig::NginxConfig(const NginxConfig& obj) {
	this->_config_file = obj.GetConfigFile();
}

NginxConfig & NginxConfig::operator=(const NginxConfig& obj) {
	this->_config_file = obj.GetConfigFile();
	return (*this);
}

std::string NginxConfig::GetConfigFile() const{
	return this->_config_file;
}