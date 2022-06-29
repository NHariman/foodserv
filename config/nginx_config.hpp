/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/29 18:04:16 by nhariman      ########   odam.nl         */
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
		struct s_components
		{
			bool	error_page = false;
			bool	access_log = false;
			bool	client_max_body_size = false;
			int		server_block = 0;
		}	components;
		
	protected:
		std::map<std::string, std::string>	global_configurations;
		std::vector<ServerBlock>			server_blocks;
		int									main_body_client_max_body_size;
		std::map<int, std::string>			error_page;
		int									access_log;


		NginxConfig(); // cant call default, as file must be added in as argument
		void	loadConfigMap(void);

	public:
		NginxConfig(std::ifstream& config_file);
		// .. bla bla add in conplien
};

#endif