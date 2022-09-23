#ifndef SETUP_HPP
# define SETUP_HPP

#include "nginx_config.hpp"
#include <iostream>
#include <stdexcept>

const char*    GetConfigLocation(int ac, const char **av);

class TooManyArgumentsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Too many arguments.";
				}
		};

#endif