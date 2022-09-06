/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The ServerSelection class takes as an argument all 
   parsed servercontexes from the nginx configuration file. 
   ServerSelection will then select the most compatible 
   servercontext to serve the request with.
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
		
		bool			SelectCompatiblePorts(std::string ports);
		void			SelectCompatibleServerNames(std::string, std::vector<ServerContext>);

	public:
		ServerSelection(std::string host, std::string port, std::vector<ServerContext>);
		ServerContext	GetChosenServerContext() const;
		std::string		GetHost();
		void			PrintChosenServerblock();
		void			PrintContextVectors();
};

#endif
