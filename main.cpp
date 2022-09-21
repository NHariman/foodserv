/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 14:43:07 by nhariman      #+#    #+#                 */
/*   Updated: 2022/09/21 22:42:15 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "src/config/nginx_config.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"
#include "src/server/socket.hpp"
#include "src/server/kernel_events.hpp"

int	main(int ac, const char **av) {
	(void)ac;

	try {
		// first read in the given configuration file
		NginxConfig input_file(GetConfigLocation(ac, av));
	
		Socket			webserver(input_file.GetServers());
		KernelEvents	events_listener(webserver.GetListeningSockets());

		
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
