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

class ServerContext : public ConfigValues {
	private:

		size_t	amount_location_context;
		bool	bool_listen;
		bool	bool_server_name;

		size_t								_server_nb;
		std::vector<LocationContext>		_location_contexts;
		std::pair<std::string, std::string>	_listen;
		std::vector<std::string>			_server_name;

		size_t					FindLocationContextEnd(std::string config_file, size_t start);
		//overridden base class functions
		void					GetDirectiveValuePairs(size_t *start_position, std::string config_file) override; // in this case i do not use override as i want to use it differently.
		void					CheckListVerification() override;
		void					SetValue(int directive, std::string value) override;
		int						IsDirective(std::string directive) override;
		void					InitChecklist() override;
		
		bool					HasDefaultLocation(std::vector<LocationContext> locations);

	public:
		ServerContext();
		ServerContext(size_t *start, std::string config_file, size_t server_nb); // uses a pointer so it can skip through the server bits on its own when it returns
		ServerContext(const ServerContext &server_context);
		ServerContext & operator= (const ServerContext &server_context);
		~ServerContext(){};
		
		// check if set
		bool						IsSet(std::string key) override;
		//getters
		std::vector<LocationContext>			GetLocationContexts() const;
		std::pair<std::string, std::string>		GetListen() const;
		std::string								GetIPAddress() const;
		std::string								GetPortNumber() const;
		std::vector<std::string>				GetServerNameVector() const;
		std::vector<ErrorPage>					GetErrorPage() const override;

		class MultipleListensException : public std::exception
		{
			public:
				MultipleListensException(size_t server) {
					_err_string = "ERROR! Multiple listen directives found in server context no. " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
				virtual ~MultipleListensException() throw() {}
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
				virtual ~DuplicateLocationUriException() throw() {}
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
				virtual ~MultipleServerNameException() throw() {}
			private:
				std::string		_err_string;
		};
		class BadInputException : public std::exception
		{
			public:
				BadInputException(size_t server) {
					_err_string = "ERROR! Bad directive input found in server context: " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
				virtual ~BadInputException() throw() {}
			private:
				std::string		_err_string;
		};
};

#endif