#include "utils.hpp"

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