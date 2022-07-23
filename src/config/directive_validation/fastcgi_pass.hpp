#ifndef FASTCGI_PASS_HPP
# define FASTCGI_PASS_HPP

#include <string>
#include "../../utils.hpp"

class FastCGIPass {
    private:
        FastCGIPass(){};
    public:
        FastCGIPass(std::string input);
        ~FastCGIPass(){};
        class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in fastcgi_pass block.";
				}
		};
};

#endif