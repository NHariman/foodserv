/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   local_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/21 12:20:26 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/config/server_context.hpp"

int main(int ac, const char **av) {
	(void)ac;
	try {
		NginxConfig		input_file(av[1]);

		std::cout << "Amount of serverblocks: " << input_file.GetServerBlockAmount() << std::endl;
		//std::cout << "Printing what is in server blocks: " << std::endl;
		//input_file.PrintServerBlocksVectors();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
