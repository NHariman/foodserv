#include "error_responses.hpp"
#include <iostream>

int	main(int ac, char **av) {
	if (ac < 2 || ac > 2)
		std::cout << GetServerErrorPage(508) << std::endl;
	else {
		int a = atoi(av[1]);
		std::cout << GetServerErrorPage(a) << std::endl;
	}
	return 0;
}