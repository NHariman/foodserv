#include <iostream>
#include <string>

int main(int ac, char **av)
{
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	if (ac < 2 || ac > 2)
		std::cerr << "Bad arguments." << std::endl;
	else
	{
		// takes the first argument path to a config file or a default path to said config file
		std::string	file_path(av[1]);
		std::cout << file_path << std::endl;
	}
	return (0);
}