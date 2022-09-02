/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The ServerSelection class takes as an argument all serverblocks
   from the nginx configuration file. 
   It will then choose the most compatible serverblock to serve the request on.
*/

#ifndef SERVER_SELECTION_HPP
# define SERVER_SELECTION_HPP

#include "server_context.hpp"

class ServerSelection {
	private:
		ServerSelection();
		std::string					_port;
		std::string					_host;
		std::vector<ServerContext>	_serverblocks;
		std::vector<ServerContext>	_compatible_serverblocks;
		ServerContext				_chosen_servercontext;

	public:
		ServerSelection(std::string host, std::string port, std::vector<ServerContext>);

		void	PrintContextVectors();
		void	PrintChosenServerblock();

		// call the request host line from michelle her code.
		// void	SplitRequestHost();
		bool	SelectCompatiblePorts(std::string ports);
		bool	SelectCompatibleServerNames(std::string, std::vector<ServerContext>);

		


		ServerContext	GetChosenServerContext() const;

		std::string		GetHost();
};

#endif
