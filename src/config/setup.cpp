#include "setup.hpp"

const char*    GetConfigLocation(int ac, const char **av) {
	const char	*location;
	if (ac > 2) {
		throw TooManyArgumentsException();
	}
	else if (ac == 1){
		location = "config_files/default.conf";
	}
	else {
		location = av[1];
	}
	return (location);
}