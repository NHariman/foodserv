/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_context.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:35:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/21 11:53:23 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONTEXT_HPP
# define SERVER_CONTEXT_HPP
#include <iostream>
#include <map>
#include "location_context.hpp"
#include "server_name.hpp"
#include "directive_validation/directive_validation.hpp"
#include "config_utils.hpp"
#include "config_interface.hpp"
#include "listen.hpp"
#include <vector>
#include <string>
#include <stdexcept>

struct t_flags_server
{


}; // check list of found keywords in ServerContext

class ServerContext : public ConfigValues {
	private:
		size_t	amount_location_context;
		bool	bool_listen;
		bool	bool_server_name;

		size_t							_server_nb;
		t_flags_server					_check_list;
		std::vector<LocationContext>	_location_contexts;
		std::pair<in_addr_t, int>		_listen; // changed by sanne
		std::vector<std::string>		_server_name; // changed by sanne
				
	public:
		ServerContext();
		ServerContext(size_t *start, std::string config_file, size_t server_nb); // uses a pointer so it can skip through the server bits on its own when it returns
		ServerContext(const ServerContext &server_context);
		ServerContext & operator= (const ServerContext &server_context);
		~ServerContext(){};
		
		// check if set
		bool						IsSet(std::string key);
		//getters
		std::vector<LocationContext>	GetLocationContexts() const;
		std::pair<in_addr_t, int>	GetListen() const;
		in_addr_t					GetIPAddress() const;
		int							GetPortNumber() const;
		std::vector<std::string>	GetServerNameVector() const;

		class MultipleListensException : public std::exception
		{
			public:
				MultipleListensException(size_t server) {
					_err_string = "ERROR! Multiple listen directives found in server context no. " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class DuplicateLocationUriException : public std::exception
		{
			public:
				DuplicateLocationUriException(size_t server, std::string uri) {
					_err_string = "ERROR! Multiple location uri directives (" + uri + ") found in server context no." + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class MultipleServerNameException : public std::exception
		{
			public:
				MultipleServerNameException(size_t server) {
					_err_string = "ERROR! Multiple server_names directives found in server context: " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		
		class MultipleAutoindexException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleAutoindexException(size_t server) {
					_err_string = "ERROR! Multiple autoindex directives detected in server context: " + std::to_string(server) + " .";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
				class MultipleReturnException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleReturnException(size_t server) {
					_err_string = "ERROR! Multiple return directives detected in server context: " + std::to_string(server) + " .";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
};

#endif