
#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP

# include <iostream>
# include <string>
#include "../config_utils.hpp"

class Autoindex {
private:
    bool _status;
    Autoindex(){};
public:
    Autoindex(std::string value);
    ~Autoindex(){};

    bool GetStatus() const;
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
					return "ERROR! Too many Arguments in autoindex.";
				}
		};
};

#endif