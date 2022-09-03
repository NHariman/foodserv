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
	: _port(port), _host(host), _serverblocks(serverblocks) {
	// host can never be empty as the default is set by nginx
	// is this needed or is default already set?
	// if (_port.size() == 0)
	// 	_port = "80";
	
	if (SelectCompatiblePorts(_port) == false) {
		if (_compatible_serverblocks.size() == 0)
			SelectCompatibleServerNames(_host, _serverblocks);
		else
			SelectCompatibleServerNames(_host, _compatible_serverblocks);
	}
}

void	ServerSelection::PrintContextVectors() {
	int		i = 1;
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		std::cout << "\n\nSERVER BLOCK NUMBER " << i << std::endl;
		std::cout << "PortNumber: " << it->GetPortNumber() << std::endl;
		std::vector<std::string> server = it->GetServerNameVector();
		if (server.size() == 0) {
			_chosen_servercontext = _compatible_serverblocks.at(0);
		}
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			std::cout << "In servername vector printing: " << std::endl;
			std::cout << *it2 << std::endl;
		}
		i++;
	}
	std::cout << std::endl;
}

void	ServerSelection::PrintChosenServerblock() {
	std::cout << "THE CHOSEN SERVER BLOCK: " << std::endl;
	std::cout << "port: " << _chosen_servercontext.GetPortNumber() << std::endl;
	std::vector<std::string> server_names = _chosen_servercontext.GetServerNameVector();
	std::cout << "server_names: ";
	for (std::vector<std::string>::iterator it = server_names.begin(); it != server_names.end(); it++)
		std::cout << *it << " ";//std::endl;
	std::cout << std::endl << std::endl;;
}

bool	ServerSelection::SelectCompatiblePorts(std::string request_port_number) {
	// see if there are server blocks with compatible port numbers
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		if (it->GetPortNumber() == request_port_number)
			_compatible_serverblocks.push_back(*it);
	}
	if (_compatible_serverblocks.size() == 1) {
		_chosen_servercontext = _compatible_serverblocks.at(0);
		return true;
	}
	return false;
}

void	ServerSelection::SelectCompatibleServerNames(std::string request_server_name, std::vector<ServerContext> server_vec) {
	for (std::vector<ServerContext>::iterator it = server_vec.begin(); it != server_vec.end(); it++) {
		std::vector<std::string> server = it->GetServerNameVector();
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			if (it2->compare(request_server_name) == 0) {
				_chosen_servercontext = *it;
				return ;
			}
			// else
				// _chosen_servercontext = _compatible_serverblocks.at(0);
		}
	}
	if (_compatible_serverblocks.size() == 0) {
		_chosen_servercontext = _serverblocks.at(0);
	}
	else
		_chosen_servercontext = _compatible_serverblocks.at(0);
}

std::string		ServerSelection::GetHost() {
	return _chosen_servercontext.GetPortNumber();
}

ServerContext	ServerSelection::GetChosenServerContext() const {
	return	_chosen_servercontext;
}

// function: print choosen server context