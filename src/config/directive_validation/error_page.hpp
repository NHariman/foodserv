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

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include "../config_utils.hpp"

void	AddToErrorPageMap(std::map<int, std::string> *map, std::string input);

class ErrorPage {

	public:
		ErrorPage(){};
		~ErrorPage(){};
		class InvalidCodeInputException : public std::exception
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
		class DuplicateErrorCodeException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Duplicate error code detected in error_page.";
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
	
		class BadErrorURIException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad error_page URI in error_page block.";
				}
		};

};

#endif