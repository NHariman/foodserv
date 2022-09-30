#ifndef ROOT_HPP
# define ROOT_HPP

#include <string>
#include "../../utils/config_utils.hpp"

class Root {
    private:
        Root(){};
    public:
        Root(std::string input);
        ~Root(){};
        class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in fastcgi_pass block.";
				}
		};
        class TooManyArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Too Many Arguments in fastcgi_pass block.";
				}
		};
};

#endif