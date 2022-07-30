/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/07/14 21:11:02 by salbregh      ########   odam.nl         */
=======
/*   Updated: 2022/07/24 12:17:19 by nhariman      ########   odam.nl         */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"

int main(int ac, const char **av) {
	(void)ac;
	try {
		NginxConfig		input_file(av[1]);

		std::cout << "Amount of serverblocks: " << input_file.GetServerContextAmount() << std::endl;
		// std::cout << "Printing what is in server blocks: " << std::endl;
		// input_file.PrintServerContextsVectors();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
