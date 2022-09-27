#include "error_responses.hpp"
#include <iostream>

int	main() {
	std::cout << GetServerErrorPage(507) << std::endl;
	return 0;
}