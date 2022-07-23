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
#include "../utils.hpp"
#include "listen.hpp"
#include <vector>
#include <string>
#include <stdexcept>

struct t_flags_server
{
	int		location_context;
	bool	listen;
	bool	server_name;
	bool	root;
	bool	index;
	bool	client_max_body_size;
	bool	error_page;
}; // check list of found keywords in ServerContext

class ServerContext {
	private:
		t_flags_server					_check_list;
		std::vector<LocationContext>	_location_contexts;
		std::pair<in_addr_t, int>		_listen; // changed by sanne
		std::vector<std::string>		_server_name; // changed by sanne
		std::string						_root;
		std::vector<std::string>		_index;
		int								_client_max_body_size;
		std::vector<ErrorPage>			_error_page;

		int							IsDirective(std::string directive);
		void						SetValue(int directive, std::string value);
		void						CheckListVerification();
		void						FindDirectiveValuePairs(size_t *start_position, std::string config_file);
		size_t						FindLocationContextEnd(std::string config_file, size_t start);
		
		
	public:
		ServerContext(size_t *start, std::string config_file); // uses a pointer so it can skip through the server bits on its own when it returns
		ServerContext();
		ServerContext(const ServerContext &server_context);
		ServerContext & operator= (const ServerContext &server_context);
		~ServerContext(){};
		
		//getters
		std::vector<LocationContext>	GetLocationContexts() const;
		std::pair<in_addr_t, int>	GetListen() const;
		in_addr_t					GetIPAddress() const;
		int							GetPortNumber() const;
		std::vector<std::string>	GetServerNameVector() const;
		std::string					GetRoot() const;
		std::vector<std::string>	GetIndex() const;
		int							GetClientMaxBodySize() const;
		std::vector<ErrorPage>		GetErrorPage() const;
		bool						IsErrorPageSet() const;
		t_flags_server				GetFlags() const;

		// exception classes
		class InvalidDirectiveException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid Key detected in Server block.";
				}
		};
		class MultipleListensException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple listen keys detected in Server block.";
				}
		};
		class MultipleRootException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple root keys detected in Server block.";
				}
		};
		class MultipleClientMaxBodySizeException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple client_max_body_size keys detected in Server block.";
				}
		};
		class DuplicateLocationUriException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Duplicate location URI detected in Server block.";
				}
		};
		class MultipleServerNameException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple server_name keys detected in Server block.";
				}
		};
		class MultipleIndexException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple index keys detected in Server block.";
				}
		};
};

#endif