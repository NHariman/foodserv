#ifndef CONFIG_UTILS_HPP
# define CONFIG_UTILS_HPP
#include <string>
#include <vector>

#include "../config/directive_validation/directive_validation.hpp"
#include <iostream>

size_t	ft_atosize_t(std::string value);
std::string	TrimValue(std::string value);
std::vector<std::string>	ToStringVector(std::string str);
bool	IsNumber(std::string input);
bool	IsUri(std::string input);
size_t	CountArguments(std::string input);
bool	IsValidHTTPCode(size_t code);
int		IsValidHTTPMethod(std::string method);
bool	HasContent(char end_char, size_t key_end, size_t value_end, std::string config);
bool	IsDirectory(std::string input);

class NegativeNumberException : public std::exception
{
	public:
		const char *what() const throw() {
			return "ERROR! Negative number detected.";
		}
};

#endif