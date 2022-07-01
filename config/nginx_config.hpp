/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/01 20:10:12 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "server_block.hpp"

class NginxConfig {
	private:
		struct s_components
		{
			bool	error_page;
			bool	access_log;
			bool	client_max_body_size;
			int		server_block;
		}	components;
		
	protected:
		std::vector<ServerBlock>			server_blocks;
		int									main_body_client_max_body_size;
		std::map<int, std::string>			error_page;
		int									access_log;
		void	ComponentChecker(s_components component);
		NginxConfig(); // cant call default, as file must be added in as argument
		void	loadConfigMap(void);

	public:
		NginxConfig(std::ifstream& config_file);
		// .. bla bla add in conplien
};

#endif