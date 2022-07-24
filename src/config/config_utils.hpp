#ifndef UTILS_HPP
# define UTILS_HPP
#include <string>
#include <vector>

long	ft_atol(std::string value);
std::string	TrimValue(std::string value);
std::vector<std::string>	ToStringVector(std::string str);
bool	IsNumber(std::string input);
bool	IsUri(std::string input);
size_t	CountArguments(std::string input);

#endif