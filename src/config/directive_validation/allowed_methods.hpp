#ifndef ALLOWED_METHODS_HPP
# define ALLOWED_METHODS_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "../config_utils.hpp"

class AllowedMethods {
    private:
		bool						_get;
		bool						_post;
		bool						_delete;

		void	ValidateMethods();

    public:
		AllowedMethods();
		AllowedMethods(std::string str);
		~AllowedMethods(){};
		AllowedMethods(AllowedMethods const &obj);
		AllowedMethods&	operator=(AllowedMethods const &obj);

		bool	GetGET() const;
		bool	GetPOST() const;
		bool	GetDELETE() const;
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
		class TooManyArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Too many Arguments in allowed_methods block.";
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