/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/18 14:36:36 by salbregh      ########   odam.nl         */
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
		std::vector<ServerBlock>	_compatible_server_blocks;
		size_t						_amount_server_blocks;
		// change this var
		ServerBlock					_the_chosen_server_block;

		NginxConfig();
		bool		IsServerBlock(std::string value, size_t *start_pos);
		void		CheckBrackets();
		void		FindServerBlocks();
		void		LoadConfigFile(std::ifstream& configuration_file);

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
		
		void	SplitRequestHost(); // split server from port in the request host header
		void	PrintServerBlocksVectors(std::vector<ServerBlock>); // for error checking
		void	ChooseServerBlock(); // make list of compatible server blocks
		void	SelectCompatiblePorts(int);
		void	SelectCompatibleServerNames(std::string, std::vector<ServerBlock>);

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
