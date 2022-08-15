#ifndef CONFIG_EXCEPTIONS_HPP
# define CONFIG_EXCEPTIONS_HPP

#include <stdexcept>

class TooManyArgumentsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Too many arguments.";
				}
		};

#endif