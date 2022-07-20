#ifndef ROOT_HPP
# define ROOT_HPP

#include <string>

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
};

#endif