// https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page

// first put everything in vectors
// then make the last value in the vector the uri
// then validate if all values before that one are numbers
// then create a map that takes a std::string in the first bit and a vector<int>
// in the second bit
// probably need a vector of maps like this tbh
// because you can assign multiple error page types

# include <map>
# include <vector>
# include <string>
#include <iostream>
# include "../../utils.hpp"

class ErrorPage {
	private:
		std::string			_uri;
		std::vector<int>	_code;
		ErrorPage(){};

		bool IsErrorCode(std::string input);
		bool IsUri(std::string input);
	
	public:
		~ErrorPage(){};
		ErrorPage(std::string input);

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
};

std::ostream& operator<<(std::ostream& os, const ErrorPage& error_page);