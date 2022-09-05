#include "location_selection.hpp"

LocationSelection::LocationSelection(ServerContext chosen_servercontext, std::string request_uri)
	: _server_context(chosen_servercontext), _request_uri(request_uri) {
	_cgi_bool = false;
	_location_context_vector = _server_context.GetLocationContexts();
	// _location_uri = _location_context.GetLocationUri();
	// make the real _request_uri

	SelectLocationContext();
	PrintLocationContext();

}

void	LocationSelection::SelectLocationContext() {
	std::string	nginx_uri;
	// set _chosen_location_context
	// vector that loops throug all location contexts
	for (std::vector<LocationContext>::const_iterator it = _location_context_vector.begin(); it != _location_context_vector.end(); it++) {
		nginx_uri = it->GetLocationUri().GetUri();
		std::cout << "nginx uri: " << nginx_uri << std::endl;
		std::cout << "request uri: " << _request_uri << std::endl;
		// now compare these against eachother and get the best match
		// if no match: return default -> default is al gezet: NIKS CHECKED DIT
		// maak een compatable vector met de mogelijkheden
		// kies daarvan de langste match
	}
}

std::string	LocationSelection::getRequestUri() const {
	return _request_uri;
}

bool		LocationSelection::isCgi() const {
	// if the directive cgi is found, this sound be set to true.
	return	_cgi_bool;
}

LocationContext	LocationSelection::getLocationContext() const {
	return _chosen_location_context;
}

void		LocationSelection::PrintLocationContext() const {
	// in the chosen server context, there should be a location context
	// find this and print all of this

	// printing all location contexts
	// std::cout << "location uri: " << _location_uri.GetUri() << std::endl;

	// location context is a vector full of locations
	// each location contexts consists of: 

}