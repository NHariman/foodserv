/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The ServerSelection class chooses the most compatible
   serverblock to serve the request on. Getters will be
   provided to use in socket.hpp and server.hpp.
*/

#include "server_selection.hpp"

ServerSelection::ServerSelection(std::vector<ServerContext> serverblocks): _serverblocks(serverblocks) {
	PrintContextVectors();
	SplitRequestHost();
}

void	ServerSelection::PrintContextVectors() {
	for (std::vector<ServerContext>::iterator it = _serverblocks.begin(); it != _serverblocks.end(); it++) {
		std::cout << "\nIn server block print for loop: " << std::endl;
		std::cout << "PortNumber: " << it->GetPortNumber() << std::endl;
		std::cout << "IPAddress: " << it->GetIPAddress() << std::endl;
		std::vector<std::string> server = it->GetServerNameVector();
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			std::cout << "In servername vector printing: " << std::endl;
			std::cout << *it2 << std::endl;
		}
	}
}

// for now use example strings that represent the host header:
// Host = uri-host [ ":" port ] ;
// string: www.example.com
// string: example.com:80
// string:
// SANNE: add the functions to select which server block to choose

void	ServerSelection::SplitRequestHost() {
	std::string	request_host = "example.com:80";
	// std::string	request_host = "www.example.com";

	// both request server_name and port_number stay empty
	std::string		request_server_name = "";
	std::string		request_port_number = "";
	unsigned long	found;

	// if a ':' is found, this means a port number is specified in the request
	// split the server_name and the port_number of the request.
	found = request_host.find(':');
	if (found != std::string::npos) {
		// request_port_number = std::stoi(request_host.substr(found + 1, request_host.length()));
		request_port_number = request_host.substr(found + 1, request_host.length());
		request_server_name = request_host.substr(0, found);
	}
	else
		request_server_name = request_host;

	std::cout << "\nrequest_port_number: " << request_port_number << std::endl;
	std::cout << "request_server_name: " << request_server_name << std::endl;

	if (request_port_number != "") {
		SelectCompatiblePorts(request_port_number);
		if (_compatible_serverblocks.size() == 1) {
			_chosen_serverblock = _compatible_serverblocks.at(0);
			return ;
		}
	}
	if (request_server_name.compare("") != 0) {
		if (_compatible_serverblocks.size() == 0)
			SelectCompatibleServerNames(request_server_name, _serverblocks);
		else
			SelectCompatibleServerNames(request_server_name, _compatible_serverblocks);
	}
	else
		_chosen_serverblock = _serverblocks.at(0);

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
				_chosen_serverblock = *it;
				return ;
			}
			else {
				std::cout << "No match found, using defaults.";
			}
		}
	}
}

std::string		ServerSelection::getHost() {
	return _chosen_serverblock.GetPortNumber();
}