/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/08/12 00:02:59 by nhariman      ########   odam.nl         */
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
	NginxConfig*	input_file;
	input_file = ConfigSetup(ac, av);
	if (!input_file)
		return (1);
	std::cout << "location uri for / " << input_file->GetMaxBodySize("localhost", "/") << std::endl;
	delete input_file;
	return (0);
}
