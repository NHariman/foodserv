/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The ServerSelection class chooses the most compatible
   serverblock to serve the request on. Getters will be
   provided to use in socket.hpp and server.hpp.
*/

#ifndef SERVER_SELECTION_HPP
# define SERVER_SELECTION_HPP

#include "server_context.hpp"
// #include "NginxConfig.hpp"

class ServerSelection {
	private:
		ServerSelection();
		std::vector<ServerContext>	_serverblocks;
		std::vector<ServerContext>	_compatible_serverblocks;
		ServerContext				_chosen_serverblock;

	public:
		ServerSelection(std::vector<ServerContext>);

		void	PrintContextVectors();
		// call the request host line from michelle her code.
		void	SplitRequestHost();
		void	SelectCompatiblePorts(std::string ports);
		void	SelectCompatibleServerNames(std::string, std::vector<ServerContext>);

		std::string		getHost();
};

#endif
