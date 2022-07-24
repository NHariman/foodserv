#include "utils.hpp"
#include <iostream>

long		ft_atol(std::string value)
{
	long	number = 0;
	long	negative = 1;
	long	i = value.find_first_not_of(" \t\n\v\f\r");
 
	if (value[i] == '-' || value[i] == '+')
	{
		if (value[i] == '-')
			negative = -1;
		i++;
	}
	while (std::isdigit(value[i]) && value[i])
	{
		number = (number * 10) + (value[i] - '0');
		i++;
	}
	return (number * negative);
}

std::string	TrimValue(std::string value){
	size_t	start = 0;
	size_t	end = 0;

	start = value.find_first_not_of(" \t\n\v\f\r");
	end = value.find_last_not_of(" \t\n\v\f\r");
	return (value.substr(start, end - start + 1));
}

std::vector<std::string>	ToStringVector(std::string str) {
	size_t	i = 0;
	size_t	start = 0;
	size_t	end = 0;
	std::string key;
	std::vector<std::string> vec;

	while (str[i]) {
		start = str.find_first_not_of(" \t\n\v\f\r", i);
		end = str.find_first_of(" \t\n\v\f\r", start);
		if (start == end)
			break ;
		key = str.substr(start, end - start);
		vec.push_back(key);
		i = end;
	}
	return (vec);
}

bool	IsNumber(std::string input) {
	size_t	i = 0;

	while (input[i]) {
		if (std::isdigit(input[i]) == 0)
			return false;
		i++;
	}
	return true;
}

bool	IsUri(std::string input) {
	std::cout << input << std::endl;
	if (input[0] == '/')
		return true;
	return false;
}
