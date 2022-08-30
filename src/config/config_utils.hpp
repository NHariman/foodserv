#ifndef CONFIG_UTILS_HPP
# define CONFIG_UTILS_HPP
#include <string>
#include <vector>

size_t	ft_atosize_t(std::string value);
std::string	TrimValue(std::string value);
std::vector<std::string>	ToStringVector(std::string str);
bool	IsNumber(std::string input);
bool	IsUri(std::string input);
size_t	CountArguments(std::string input);
bool	IsValidHTTPCode(size_t code);

class NegativeNumberException : public std::exception
{
	public:
		const char *what() const throw() {
			return "ERROR! Negative number detected.";
		}
};

#endif