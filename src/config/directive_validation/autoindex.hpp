
#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP

# include <iostream>
# include <string>
#include "../../utils/config_utils.hpp"

bool SetAutoindex(std::string value);

class Autoindex {
private:
public:
    Autoindex(){};
    ~Autoindex(){};
    class InvalidAutoindexException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid autoindex value detected in LocationBlock.";
				}
		};
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in autoindex.";
				}
		};
		class TooManyArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Too many arguments in autoindex.";
				}
		};
};

#endif