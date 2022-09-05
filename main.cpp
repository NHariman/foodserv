/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 12:26:13 by salbregh      #+#    #+#                 */
/*   Updated: 2022/09/05 12:26:39 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "src/config/nginx_config.hpp"
// #include "src/basic_server/listening_socket.hpp"
// #include "src/basic_server/kernel_event.hpp"
#include "src/config/server_selection.hpp"

int	main(int ac, const char **av) {
	(void)ac;
	try {
		// 1. all parsing of config.
		NginxConfig		input_file(av[1]);

		// 2. start op the server: 
		// // ListeningSocket	*sock = new ListeningSocket("::", chosen_serverblock.getHost());
		// // KernelEvent	*webserver = new KernelEvent(sock->getListeningSocket());
		
		// 3. get in a request
		// blabla requestclass()

		// 4. Server Selection() > take the whole config file,  only contains the server block

		// if host is empty should be 80
		ServerSelection	serverblock_selection("hell_yeah", "80", input_file.GetServers());
		
		// // add exceptions in the server_selection class to make it able to throw.
		// std::cout << "Amount of serverblocks: " << input_file.GetServerContextAmount() << std::endl;
		// ServerSelection	chosen_serverblock(input_file.GetServers());

		
		// std::cout << "GETHOST: " << chosen_serverblock.getHost();
		// // now initialize the kqueue with the newly opened listening socket.

		// // delete sock;
		// // delete webserver;
	
		ServerSelection	serverblock_selection2("localhost", "80", input_file.GetServers());
		// add exceptions in the server_selection class to make it able to throw.
		std::cout << "Amount of serverblocks: " << input_file.GetServerContextAmount() << std::endl;

	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	


	// delete sock;
	// delete webserver;
	
	return (0);
}
