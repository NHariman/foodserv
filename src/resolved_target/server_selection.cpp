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

#include "server_selection.hpp"

ServerSelection::ServerSelection(std::string host, std::string port, std::vector<ServerContext> serverblocks)
	: _port(port), _host(host), _serverblocks(serverblocks) {
	if (SelectCompatiblePorts(_port) == false) {
		if (_compatible_serverblocks.size() == 0)
			SelectCompatibleServerNames(_host, _serverblocks);
		else
			SelectCompatibleServerNames(_host, _compatible_serverblocks);
	}
}

bool	ServerSelection::SelectCompatiblePorts(std::string request_port_number) {
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
		}
	}
	if (_compatible_serverblocks.size() == 0)
		_chosen_servercontext = _serverblocks.at(0);
	else
		_chosen_servercontext = _compatible_serverblocks.at(0);
}

std::string		ServerSelection::GetHost() {
	return _chosen_servercontext.GetPortNumber();
}

ServerContext	ServerSelection::GetChosenServerContext() const {
	return	_chosen_servercontext;
}

/* PRINT FUNCTIONS FOR DEBUGGING */
void	ServerSelection::PrintContextVectors() {
	int		i = 1;
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		std::cout << "\n\nSERVER BLOCK NUMBER " << i << std::endl;
		std::cout << "PortNumber: " << it->GetPortNumber() << std::endl;
		std::vector<std::string> server = it->GetServerNameVector();
		if (server.size() != 0) {
			for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
				std::cout << "In servername vector printing: " << std::endl;
				std::cout << *it2 << std::endl;
			}
			i++;
		}
	}
	std::cout << std::endl;
}

void	ServerSelection::PrintChosenServerblock() {
	std::cout << "THE CHOSEN SERVER BLOCK: " << std::endl;
	std::cout << "port: " << _chosen_servercontext.GetPortNumber() << std::endl;
	std::vector<std::string> server_names = _chosen_servercontext.GetServerNameVector();
	if (server_names.size() != 0) {
		std::cout << "server_names: ";
		for (std::vector<std::string>::iterator it = server_names.begin(); it != server_names.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl << std::endl;
	}
}
