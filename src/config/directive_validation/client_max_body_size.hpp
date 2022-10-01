#ifndef CLIENT_MAX_BODY_SIZE_HPP
# define CLIENT_MAX_BODY_SIZE_HPP

#include <iostream>
#include <stdexcept>
#include "../../utils/config_utils.hpp"

/*
https://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size
if client_max_body_size is smaller than the file size trying to be uploaded it gives a:
413 error (Request Entity too large)
*/

class ClientMaxBodySize {
    private:
        size_t     _value;
    
    public:
        ClientMaxBodySize();
        ClientMaxBodySize(std::string value);
        size_t     GetValue() const;

        class InvalidClientMaxBodySizeException : public std::exception
        {
            public:
                const char *what() const throw() {
                    return "ERROR! Invalid client_max_body_size in location block.";
                }
        };   
        class TooLargeClientMaxBodySizeException : public std::exception
        {
            public:
                const char *what() const throw() {
                    return "ERROR! Invalid client_max_body_size, size too large in location block.";
                }
        };
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in client_max_body_size block.";
				}
		};
};

int PrintValue(std::string value);

#endif