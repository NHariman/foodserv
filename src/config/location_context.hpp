
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
class LocationContext : public ConfigValues {
	private:
		bool						bool_uri;
		bool						bool_fastcgi_pass;
		bool						bool_allowed_methods;	
		LocationUri					_location_uri;
		std::string					_fastcgi_pass;
		AllowedMethods				_allowed_methods;

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
		std::string					GetFastCGIPass() const;
		AllowedMethods				GetAllowedMethods() const;
		// overridden getters
		bool						GetAutoindex() const override;
		std::string					GetRoot() const override;
		std::vector<std::string>	GetIndex() const override;
		size_t						GetClientMaxBodySize() const override;
		std::vector<ErrorPage>		GetErrorPage() const override;
		
		class MultipleFastCGIPassException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleFastCGIPassException(std::string uri) {
					_err_string = "ERROR! Multiple fastcgi_pass directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~MultipleFastCGIPassException() throw() {}
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