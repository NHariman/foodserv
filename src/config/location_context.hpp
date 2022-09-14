
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
					_err_string = "ERROR! Invalid input detected in Location Context:" + uri + ".";
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

		class RootAndAliasException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				RootAndAliasException(std::string uri) {
					_err_string = "ERROR! Location Context:" + uri + " contains both alias and root, please only use one.";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~RootAndAliasException() throw() {}
		};
};

#endif