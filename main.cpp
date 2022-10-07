#include "src/config/nginx_config.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"
#include "src/server/socket.hpp"
#include "src/server/kernel_events.hpp"

int	main(int ac, const char **av) {
	try {
		// first read in the given configuration file
		NginxConfig input_file(GetConfigLocation(ac, av));
	
		Socket			listening_sockets(input_file.GetServers());
		KernelEvents	webserver(&input_file, listening_sockets.GetListeningSockets());
		

		webserver.KernelEventLoop();

		
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
}
