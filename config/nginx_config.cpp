/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/17 15:59:46 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"

// default constructor
NginxConfig::NginxConfig() {} 

// constructor which holds the file name of the nginx config
NginxConfig::NginxConfig(char *config_file) {
	// step 1. check if string is not empty
	if (!config_file) {
		// throw error
	}
	// step 2. check if string is an actual config file by trying to open it
	// step 3. start parsing the config file
}

void	NginxConfig::loadConfigMap() {}


