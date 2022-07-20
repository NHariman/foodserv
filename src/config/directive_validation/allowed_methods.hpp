#ifndef ALLOWED_METHODS_HPP
# define ALLOWED_METHODS_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include "../../utils.hpp"

class AllowedMethods {
    private:
		bool						_is_set;
        std::vector<std::string>    _methods;

		void	ValidateMethods();

    public:
		AllowedMethods();
		AllowedMethods(std::string str);
		~AllowedMethods(){};
		AllowedMethods(AllowedMethods const &obj);
		AllowedMethods&	operator=(AllowedMethods const &obj);

		std::vector<std::string>	GetAllowedMethods() const;
		void		PrintMethods();
		bool		IsSet() const;
		class BadMethodException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad Method in allowed_methods detected in LocationBlock.";
				}
		};
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in allowed_methods block.";
				}
		};
		class EmptyMethodVectorException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! empty vector, no methods set in allowed_methods block.";
				}
		};
};

#endif