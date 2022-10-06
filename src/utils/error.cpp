#include <iostream>

void	error_exit(std::string const& error_message) {
	std::cerr << error_message << std::endl;
	exit(1);
}
