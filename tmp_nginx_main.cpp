/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tmp_nginx_main.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/08/12 12:44:04 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/server.hpp"
#include "src/config/server_selection.hpp"
#include "src/config/setup.hpp"



int	main(int ac, const char **av) {
	try {

		NginxConfig input_file(GetConfigLocation(ac, av));
		std::cout << "location uri for / " << input_file.GetMaxBodySize("localhost", "/test") << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
}
