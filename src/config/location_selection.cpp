#include "location_selection.hpp"

/*
	HOW THE MATCHING IS DONE
	so basically we will only look for the prefix matches
	so the request uri must AT LEAST match the nginx uri given
	if multiple matches are find, we will choose the longest match


*/

LocationSelection::LocationSelection(ServerContext chosen_servercontext, std::string request_uri)
	: _server_context(chosen_servercontext), _request_uri(request_uri) {
	// _cgi_bool = false;
	_location_context_vector = _server_context.GetLocationContexts();
	std::cout << _location_context_vector.size() << std::endl;
	// make the real _request_uri

	PrintLocationContext(_location_context_vector);
	SelectLocationContext();
	PrintLocationContext(_compatible_locationblocks);
	if (_compatible_locationblocks.size() == 0)
		_chosen_location_context = _location_context_vector.at(0);
	else if (_compatible_locationblocks.size() == 1)
		_chosen_location_context = _compatible_locationblocks.at(0);
	else
		GetLongestMatch();
}

void	LocationSelection::SelectLocationContext() {
	std::string	config_uri;
	// set _chosen_location_context
	// vector that loops throug all location contexts
	for (std::vector<LocationContext>::const_iterator it = _location_context_vector.begin(); it != _location_context_vector.end(); it++) {
		config_uri = it->GetLocationUri().GetUri();
		std::cout << "\nconfig uri: " << config_uri << std::endl;
		std::cout << "request uri: " << _request_uri << std::endl << std::endl;
		// now compare these against eachother and get the best match
	
		// // config uri moet tenmisnte in the request uri zitten
		// std::cout << "size config_uri: " << config_uri.size() << std::endl;
		// std::cout << "size request_uri: " << _request_uri.size() << std::endl;

		std::string	prefix_check = _request_uri.substr(0, config_uri.size());
		
		

		// std::cout << "SUBSTR: " << _request_uri.substr(0, config_uri.size()) << std::endl;
		// if (_request_uri.substr(0, config_uri.size()))
		if (prefix_check.compare(config_uri) == 0) {
			std::cout << "appended" << std::endl;
			_compatible_locationblocks.push_back(*it);
		}

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

void		LocationSelection::GetLongestMatch() {
	std::cout << "request uri: " << _request_uri << std::endl;
	std::string		config_uri;
	size_t			longest_match = 0;
	LocationContext	tmp;
	
	// loop through all compatible matches
	// choose the longest one
	for (std::vector<LocationContext>::const_iterator it = _compatible_locationblocks.begin(); it != _compatible_locationblocks.end(); it++) {
		int		match_size = 0;
		config_uri = it->GetLocationUri().GetUri();
		std::cout << "config_uri: " << config_uri << std::endl;

		for (size_t i = 0; i < config_uri.size(); i++) {
			if (config_uri[i] == _request_uri[i])
				match_size++;
			if (match_size > longest_match)
				tmp = *it;
		}
	}
	std::cout << "the chosen location block is: " << tmp.GetLocationUri().GetUri() << std::endl;
	_chosen_location_context = tmp;
}

void		LocationSelection::PrintLocationContext(std::vector<LocationContext> location_context) const {
	std::string config_uri;
	for (std::vector<LocationContext>::const_iterator it = location_context.begin(); it != location_context.end(); it++) {
		config_uri = it->GetLocationUri().GetUri();
		std::cout << config_uri << std::endl;
	}
}