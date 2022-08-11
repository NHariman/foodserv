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
		size_t							_server_nb;
		t_flags_server					_check_list;
		std::vector<LocationContext>	_location_contexts;
		std::pair<in_addr_t, int>		_listen; // changed by sanne
		std::vector<std::string>		_server_name; // changed by sanne
		std::string						_root;
		std::vector<std::string>		_index;
		size_t							_client_max_body_size;
		std::vector<ErrorPage>			_error_page;

		int							IsDirective(std::string directive);
		void						SetValue(int directive, std::string value);
		void						CheckListVerification();
		void						FindDirectiveValuePairs(size_t *start_position, std::string config_file);
		size_t						FindLocationContextEnd(std::string config_file, size_t start);
		void						InitChecklist();
		void						CopyChecklist(t_flags_server obj_checklist);
		
		
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
		std::string					GetRoot() const;
		std::vector<std::string>	GetIndex() const;
		size_t						GetClientMaxBodySize() const;
		std::vector<ErrorPage>		GetErrorPage() const;
		bool						HasErrorPage() const;
		t_flags_server				GetFlags() const;

		// exception classes
		class InvalidDirectiveException : public std::exception
		{
			public:
				InvalidDirectiveException(std::string directive, size_t server) {
					_err_string = "ERROR! Multiple invalid directive (" + directive + ") in server context no." + std::to_string(server) + " .";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class MultipleListensException : public std::exception
		{
			public:
				MultipleListensException(size_t server) {
					_err_string = "ERROR! Multiple listen directives found in server context no. " + std::to_string(server) + " .";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class MultipleRootException : public std::exception
		{
			public:
				MultipleRootException(size_t server) {
					_err_string = "ERROR! Multiple root directives found in server context: " + std::to_string(server) + " .";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class MultipleClientMaxBodySizeException : public std::exception
		{
			public:
				MultipleClientMaxBodySizeException(size_t server) {
					_err_string = "ERROR! Multiple client_max_body_size directives found in server context: " + std::to_string(server) + " .";
				};
				const char *what() const throw() {
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
				const char *what() const throw() {
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
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class MultipleIndexException : public std::exception
		{
			public:
				MultipleIndexException(size_t server) {
					_err_string = "ERROR! Multiple index directives found in server context: " + std::to_string(server) + " .";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class InvalidDirectiveSetCheckException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Trying to check if a nonexistent directive has been set in server context.";
				}
		};
		class DirectiveNotSetException : public std::exception
		{
			public:
				DirectiveNotSetException(std::string directive, size_t server) {
					_err_string = "WARNING! Get attempt failed, directive: " + directive + " was not set in server no." + std::to_string(server) + ".";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
};

#endif