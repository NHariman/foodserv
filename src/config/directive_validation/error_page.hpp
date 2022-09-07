// https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page

// first put everything in vectors
// then make the last value in the vector the uri
// then validate if all values before that one are numbers
// then create a map that takes a std::string in the first bit and a vector<int>
// in the second bit
// probably need a vector of maps like this tbh
// because you can assign multiple error page types
#ifndef ERROR_PAGE_HPP
# define ERROR_PAGE_HPP

# include <vector>
# include <string>
# include <iostream>
# include "../config_utils.hpp"

class ErrorPage {
	private:
		bool				_is_set;
		std::string			_uri;
		std::vector<int>	_code;
		ErrorPage();
	
	public:
		~ErrorPage(){};
		ErrorPage(std::string input);
		ErrorPage(ErrorPage const &obj);
		ErrorPage&	operator=(ErrorPage const & obj);

		bool				IsSet() const;
		std::string			GetUri() const;
		std::vector<int>	GetCodes() const;
		void				PrintCodes() const;
		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid error code detected in error_page.";
				}
		};
		class DuplicateUriException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Duplicate Uri detected in error_page.";
				}
		};
		class BadErrorCodeException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad error code, must be between 300 and 599 in error_page block.";
				}
		};
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in error_page block.";
				}
		};
};

std::ostream& operator<<(std::ostream& os, const ErrorPage& error_page);

#endif