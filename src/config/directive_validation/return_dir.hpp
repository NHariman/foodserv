// https://www.journaldev.com/26864/nginx-rewrite-url-rules
// http://nginx.org/en/docs/http/ngx_http_rewrite_module.html#return

#ifndef RETURN_DIR_HPP
# define RETURN_DIR_HPP

#include <string>
#include "../config_utils.hpp"

class ReturnDir {
    private:
        int _code;
        std::string _url;
    public:
        ReturnDir(){};
        ReturnDir(std::string input);
        ~ReturnDir(){};
        ReturnDir(ReturnDir const &obj);
        ReturnDir& operator=(ReturnDir const &obj);

        int     GetCode() const;
        std::string GetUrl() const;
        class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! missing value in return in location block.";
				}
		};
        class InvalidReturnCodeException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid return code in return in location block.";
				}
		};
        class InvalidAmountOfArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid amount of arguments in return in location block.";
				}
		};
};

#endif