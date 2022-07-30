/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/07/18 14:36:36 by salbregh      ########   odam.nl         */
=======
/*   Updated: 2022/07/24 13:58:49 by nhariman      ########   odam.nl         */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "server_context.hpp"
#include "config_utils.hpp"

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
<<<<<<< HEAD
		std::vector<ServerBlock>	_servers;
		std::vector<ServerBlock>	_compatible_server_blocks;
		size_t						_amount_server_blocks;
		// change this var
		ServerBlock					_the_chosen_server_block;
=======
		std::vector<ServerContext>	_servers;
		size_t						_amount_server_contexts;
>>>>>>> origin

		NginxConfig();
		bool		IsServerContext(std::string value, size_t *start_pos);
		void		CheckBrackets();
<<<<<<< HEAD
		void		FindServerBlocks();
		void		LoadConfigFile(std::ifstream& configuration_file);
=======
		void		FindServerContexts();
		void		LoadConfigFile(std::ifstream&	configuration_file);
>>>>>>> origin

	public:
		// coplien form
		NginxConfig(const char*	location);
		NginxConfig(const NginxConfig& obj);
		~NginxConfig();
		NginxConfig & operator=(const NginxConfig& obj);

		// getters
		std::string	GetConfigFile() const;
		size_t		GetServerContextAmount() const;
		std::vector<ServerContext>	GetServers() const;
		
<<<<<<< HEAD
		void	SplitRequestHost(); // split server from port in the request host header
		void	PrintServerBlocksVectors(std::vector<ServerBlock>); // for error checking
		void	ChooseServerBlock(); // make list of compatible server blocks
		void	SelectCompatiblePorts(int);
		void	SelectCompatibleServerNames(std::string, std::vector<ServerBlock>);
=======
		// SANNE: adding in a function for the server block algorithm
		// you have a vector full of server blocks _servers,
		// first print the outcome of this vector?
		void	PrintServerContextsVectors();
>>>>>>> origin

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
		
		class NoServerContextsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! No servers detected.";
				}
		};

		class BadServerContextException : public std::exception {
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
