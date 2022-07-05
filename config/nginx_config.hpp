/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/05 19:59:18 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "server_block.hpp"

// Coplien form:

// class A final
// {
//    public:
//       A ();
//       A (const A &a);
//       ~A ();
//       A & operator = (const A &a);
// };


class NginxConfig {
	private:
		std::string					_config_file;
		std::vector<ServerBlock>	_servers;
		size_t						_amount_server_blocks;

		bool		IsServerBlock(size_t *start_position);

	public:
		// coplien form
		NginxConfig();
		NginxConfig(const NginxConfig& obj);
		~NginxConfig(){};
		NginxConfig & operator= (const NginxConfig& obj);

		std::string	GetConfigFile() const;
		size_t		FindServerBlocks();
		void		LoadConfigFile(std::ifstream&	configuration_file);
		size_t		GetServerBlockAmount() const;
		std::vector<ServerBlock>	GetServers() const;
		// NginxConfig(); // sets defaults
		// int		ParseConfigFile(std::ifstream& config_file);
		// .. bla bla add in conplien
};

#endif