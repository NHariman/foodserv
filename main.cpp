/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/07 21:29:04 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "config/nginx_config.hpp"
#include "config/server_block.hpp"

int main(int ac, const char **av) {
	// parse av[1] and use gnl or something like that to get the data out
	// put the info in classes intended per information
	try {
		NginxConfig		input_file(av[1]);

		std::cout << "Amount of serverblocks: " << input_file.GetServerBlockAmount() << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
