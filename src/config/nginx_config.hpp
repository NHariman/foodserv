/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/14 21:07:47 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
		bool		IsServerBlock(std::string value, size_t *start_pos);
		void		CheckBrackets();
		void		FindServerBlocks();
		void		LoadConfigFile(std::ifstream&	configuration_file);

	public:
		// coplien form
		NginxConfig(const char*	location);
		NginxConfig(const NginxConfig& obj);
		~NginxConfig();
		NginxConfig & operator=(const NginxConfig& obj);

		// getters
		std::string	GetConfigFile() const;
		size_t		GetServerBlockAmount() const;
		std::vector<ServerBlock>	GetServers() const;
		
		// SANNE: adding in a function for the server block algorithm
		// you have a vector full of server blocks _servers,
		// first print the outcome of this vector?
		void	PrintServerBlocksVectors();
		void	ChooseServerBlock();

		//exceptions
		class GetLineFailureException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! std::getline failure.";
				}
		};
		
		class OpenBracketsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Open brackets detected.";
				}
		};
		
		class NoServerBlocksException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! No servers detected.";
				}
		};

		class BadServerBlockException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Bad server keyword detected.";
				}
		};
		
		class InvalidFileLocationException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Cannot open specified file.";
				}
		};
};

#endif
