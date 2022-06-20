/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/20 20:54:50 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "ServerBlock.hpp"

class NginxConfig {
	private:
		std::map<std::string, std::string>	global_configurations;
		std::vector<ServerBlock>			*server_blocks;
		int									main_body_client_max_body_size;
		std::map<int, std::string>			error_page;


		NginxConfig(); // cant call default, as file must be added in as argument
		void	loadConfigMap(void);

	public:
		NginxConfig(std::ifstream& config_file);
		// .. bla bla add in conplien
};

#endif