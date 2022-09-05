#include "location_selection.hpp"

LocationSelection::LocationSelection(ServerContext chosen_servercontext, std::string request_uri)
	: _server_context(chosen_servercontext), _request_uri(request_uri) {
	_cgi_bool = false;
	_location_context = _server_context.GetLocationContexts();
	_location_uri = _location_context.GetLocationUri();
	// make the real _request_uri

	PrintLocationContext();
}

std::string	LocationSelection::getRequestUri() const {
	return _request_uri;
}

bool		LocationSelection::isCgi() const {
	// if the directive cgi is found, this sound be set to true.
	return	_cgi_bool;
}

void		LocationSelection::PrintLocationContext() const {
	// in the chosen server context, there should be a location context
	// find this and print all of this

	// printing all location contexts
	std::cout << "location uri: " << _location_uri.GetUri() << std::endl;

}