/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The ServerSelection class takes as an argument all serverblocks
   from the nginx configuration file. 
   It will then choose the most compatible serverblock to serve the request on.

	TODO: what getters and setters do I need
*/

#include "server_selection.hpp"

ServerSelection::ServerSelection(std::string host, std::string port, std::vector<ServerContext> serverblocks)
	: _host(host), _port(port), _serverblocks(serverblocks) {
	// host can never be empty as the default is set by nginx
	if (_port.size() == 0)
		_port = "80";
	
	PrintContextVectors();

	SelectCompatiblePorts(_port);
	SelectCompatibleServerNames(_host, _compatible_serverblocks);
}

void	ServerSelection::PrintContextVectors() {
	int		i = 1;
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		std::cout << "\n\nNUMBER " << i << std::endl;
		std::cout << "In server block print for loop: " << std::endl;
		std::cout << "PortNumber: " << it->GetPortNumber() << std::endl;
		std::vector<std::string> server = it->GetServerNameVector();
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			std::cout << "In servername vector printing: " << std::endl;
			std::cout << *it2 << std::endl;
		}
		i++;
	}
}

void	ServerSelection::SelectCompatiblePorts(std::string request_port_number) {
	// see if there are server blocks with compatible port numbers
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		if (it->GetPortNumber() == request_port_number) {
			std::cout << "A compatible server block is found based on port number." << std::endl;
			_compatible_serverblocks.push_back(*it);
		}
	}
}

void	ServerSelection::SelectCompatibleServerNames(std::string request_server_name, std::vector<ServerContext> server_vec) {
	for (std::vector<ServerContext>::iterator it = server_vec.begin(); it != server_vec.end(); it++) {
		std::vector<std::string> server = it->GetServerNameVector();
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			std::cout << "IN COMPATIBLE SERVERNAMES: " << std::endl;
			std::cout << *it2 << std::endl;
			if (it2->compare(request_server_name) == 0) {
				std::cout << "SERVER BLOCK MATCH FOUND.";
				_chosen_servercontext = *it;
				return ;
			}
			else {
				std::cout << "No match found, using defaults.";
			}
		}
	}
}

std::string		ServerSelection::GetHost() {
	return _chosen_servercontext.GetPortNumber();
}

ServerContext	ServerSelection::GetChosenServerContext() const {
	return	_chosen_servercontext;
}

// function: print choosen server context