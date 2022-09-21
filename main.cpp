/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/09/21 11:44:14 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "src/config/nginx_config.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"

int	main(int ac, const char **av) {
	(void)ac;

	try {
		// first read in the given configuration file
		NginxConfig input_file(GetConfigLocation(ac, av));
		
		Server		webserver(&input_file);

		// TO DO
		// recreate server 
		// create listening socket vector of all ports defined in nginx config
		
		// then start up the webserver 
		// within the kernel event:
		// KernelEvent webserver('');
		
		// with the request received from the webserver 
		// get the target values: servername, portnumber and requst uri.
		// with this information, look which files have to be serverd
		TargetConfig target;
		target.Setup(&input_file, "localhost", "80", "/");

		// tell the webserver that you are ready to write to the client,
		// and give it the path to write to, serve file file.

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return (0);
	
	// ServerSelection	chosen_serverblock(input_file.GetServers());
	// Server servie(80, INADDR_ANY);c
	
	return (0);
}
