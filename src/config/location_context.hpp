
#ifndef LOCATION_CONTEXT_HPP
# define LOCATION_CONTEXT_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "config_utils.hpp"
#include "directive_validation/directive_validation.hpp"

struct t_flags_location
{
	bool	uri;
	bool	autoindex;
	bool	root;
	bool	index;
	bool	client_max_body_size;
	bool	error_page;
	bool	fastcgi_pass;
	bool	allowed_methods;
	bool	return_dir;
}; // check list of found keywords in LocationContext

// actually this is called a context (sad face)
class LocationContext {
	private:
		t_flags_location			_check_list;
		LocationUri					_location_uri;
		bool						_autoindex;
		std::string					_root;
		std::vector<std::string>	_index;
		size_t						_client_max_body_size;
		std::vector<ErrorPage>		_error_page;
		std::string					_fastcgi_pass;
		AllowedMethods				_allowed_methods;
		ReturnDir					_return_dir;

		void						InitChecklist();
		void						CopyChecklist(t_flags_location obj_checklist);
		void						GetDirectiveValuePairs(std::string data);
		int							IsDirective(std::string directive);
		void						SetValue(int directive, std::string input);
		void						CheckListVerification();

	public:
		LocationContext();
		LocationContext(std::string data);
		LocationContext(LocationContext const &location_context);
		LocationContext& operator= (LocationContext const &location_context);
		~LocationContext(){};

		// check if something has been set or not
		bool						IsSet(std::string key);
		// getters
		t_flags_location			GetFlags() const;
		LocationUri					GetLocationUri() const;
		bool						GetAutoindex() const;
		std::string					GetRoot() const;
		std::vector<std::string>	GetIndex() const;
		size_t						GetClientMaxBodySize() const;
		std::string					GetFastCGIPass() const;
		std::vector<ErrorPage>		GetErrorPage() const;
		AllowedMethods				GetAllowedMethods() const;

		// exception classes
		class InvalidDirectiveException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				InvalidDirectiveException(std::string uri) {
					_err_string = "ERROR! Invalid directive detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class MultipleAutoindexException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleAutoindexException(std::string uri) {
					_err_string = "ERROR! Multiple autoindex directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class MultipleRootException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleRootException(std::string uri) {
					_err_string = "ERROR! Multiple root directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class MultipleIndexException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleIndexException(std::string uri) {
					_err_string = "ERROR! Multiple index directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class MultipleErrorPageException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleErrorPageException(std::string uri) {
					_err_string = "ERROR! Multiple error_page directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
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
		};
		class MultipleClientMaxBodySizeException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleClientMaxBodySizeException(std::string uri) {
					_err_string = "ERROR! Multiple client_max_body_size directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
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
		};
		class MultipleReturnException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleReturnException(std::string uri) {
					_err_string = "ERROR! Multiple return directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class InvalidDirectiveSetCheckException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				InvalidDirectiveSetCheckException(std::string uri) {
					_err_string = "Invalid directive detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class DirectiveNotSetException : public std::exception
		{
			public:
				DirectiveNotSetException(std::string directive) {
					_err_string = "WARNING! Get attempt failed, directive: " + directive + " was not set.";
				};
				const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
};

#endif