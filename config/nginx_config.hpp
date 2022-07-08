/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/09 00:07:36 by nhariman      ########   odam.nl         */
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

// TODO:
// create basic error checking, open brackets etc.

class NginxConfig {
	private:
		std::string					_config_file;
		std::vector<ServerBlock>	_servers;
		size_t						_amount_server_blocks;

		NginxConfig();
		bool		IsServerBlock(size_t *start_position);
		void		CheckBrackets();
		void		FindServerBlocks();
		void		LoadConfigFile(std::ifstream&	configuration_file);

	public:
		// coplien form
		NginxConfig(const char*		location);
		NginxConfig(const NginxConfig& obj);
		~NginxConfig(){};
		NginxConfig & operator= (const NginxConfig& obj);

		// getters
		std::string	GetConfigFile() const;
		size_t		GetServerBlockAmount() const;
		std::vector<ServerBlock>	GetServers() const;

		//exceptions
		class GetLineFailureException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! std::getline failure.";
				}
		};
		class OpenBracketsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Open brackets detected.";
				}
		};
		class BadKeywordException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad Keyword, not a server block.";
				}
		};
		class NoServerBlocksException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! No servers detected.";
				}
		};
		class BadServerBlockException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! No servers detected.";
				}
		};
		class InvalidFileLocationException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Cannot open specified file.";
				}
		};
};

#endif