
#ifndef LOCATION_CONTEXT_HPP
# define LOCATION_CONTEXT_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "config_utils.hpp"
#include "config_interface.hpp"
#include "directive_validation/directive_validation.hpp"

// actually this is called a context (sad face)
class LocationContext : virtual public ConfigValues {
	protected:
		bool						bool_uri;
		bool						bool_cgi_pass;
		bool						bool_allowed_methods;
		bool						bool_alias;
		LocationUri					_location_uri;
		CGIPass						_cgi_pass;
		AllowedMethods				_allowed_methods;
		std::string					_alias;

		void						GetDirectiveValuePairs(std::string data) override;
		int							IsDirective(std::string directive) override;
		void						SetValue(int directive, std::string input) override;
		void						CheckListVerification() override;
		virtual void				InitChecklist() override;

	public:
		LocationContext();
		LocationContext(std::string data);
		LocationContext(LocationContext const &location_context);
		LocationContext& operator= (LocationContext const &location_context);
		virtual ~LocationContext(){};

		// location context specific getters
		bool						IsSet(std::string directive) override;
		// getters
		LocationUri					GetLocationUri() const;
		CGIPass						GetCGIPass() const;
		AllowedMethods				GetAllowedMethods() const;
		std::string					GetAlias() const;
		// overridden getters
		bool						GetAutoindex() const override;
		std::string					GetRoot() const override;
		std::vector<std::string>	GetIndex() const override;
		size_t						GetClientMaxBodySize() const override;
		std::vector<ErrorPage>		GetErrorPage() const override;
		ReturnDir					GetReturn() const override;
		
		class MultipleCGIPassException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleCGIPassException(std::string uri) {
					_err_string = "ERROR! Multiple cgi_pass directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~MultipleCGIPassException() throw() {}
		};

		class MultipleAllowedMethodsException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleAllowedMethodsException(std::string uri) {
					_err_string = "ERROR! Multiple allowed_methods directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~MultipleAllowedMethodsException() throw() {}
		};

		class BadInputException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				BadInputException(std::string uri) {
					_err_string = "ERROR! Multiple index directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~BadInputException() throw() {}
		};
		class MultipleAliasException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleAliasException(std::string uri) {
					_err_string = "ERROR! Multiple alias directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~MultipleAliasException() throw() {}
		};

		class BadURIException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				BadURIException(std::string uri) {
					_err_string = "ERROR! Bad URI detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~BadURIException() throw() {}
		};
};

#endif