/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/08/25 12:19:16 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
#include "src/basic_server/listening_socket.hpp"
#include "src/basic_server/kernel_event.hpp"
#include "src/config/server_selection.hpp"

int	main(int ac, const char **av) {
	(void)ac;
	try {
		NginxConfig		input_file(av[1]);

		// ServerSelection	serverblock_selection(input_file.GetServers());
		
		// // add exceptions in the server_selection class to make it able to throw.
		// std::cout << "Amount of serverblocks: " << input_file.GetServerContextAmount() << std::endl;
		// ServerSelection	chosen_serverblock(input_file.GetServers());

		
		// std::cout << "GETHOST: " << chosen_serverblock.getHost();
		// // now initialize the kqueue with the newly opened listening socket.
		// // ListeningSocket	*sock = new ListeningSocket("::", chosen_serverblock.getHost());
		// // KernelEvent	*webserver = new KernelEvent(sock->getListeningSocket());

		// // delete sock;
		// // delete webserver;
	
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	


	// delete sock;
	// delete webserver;
	
	return (0);
}
