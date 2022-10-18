#include "src/config/nginx_config.hpp"
#include "src/config/setup.hpp"
#include "src/resolved_target/target_config.hpp"
#include "src/server/socket.hpp"
#include "src/server/kernel_events.hpp"
#include "src/utils/utils.hpp"

int	main(int ac, const char **av) {
	try {
		NginxConfig input_file(GetConfigLocation(ac, av));
	
		Socket			listening_sockets(input_file.GetServers());
		KernelEvents	webserver(&input_file, listening_sockets.GetListeningSockets());
		
		webserver.KernelEventLoop();
	}
	catch (const std::exception& e) {
		error_exit(e.what());
	}
	return (0);
}
