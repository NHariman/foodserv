#include "location_selection.hpp"

/*
	HOW THE MATCHING IS DONE
	so basically we will only look for the prefix matches
	so the request uri must AT LEAST match the nginx uri given
	if multiple matches are find, we will choose the longest match
*/

LocationSelection::LocationSelection(ServerContext chosen_servercontext, std::string request_uri)
	: _request_uri(request_uri), _server_context(chosen_servercontext) {
	_location_context_vector = _server_context.GetLocationContexts();

	SelectLocationContext();
	if (_compatible_locationblocks.size() == 0)
		_chosen_location_context = _location_context_vector.at(0);
	else if (_compatible_locationblocks.size() == 1)
		_chosen_location_context = _compatible_locationblocks.at(0);
	else
		GetLongestMatch();
}

void	LocationSelection::SelectLocationContext() {
	std::string	config_uri;

	for (std::vector<LocationContext>::const_iterator it = _location_context_vector.begin(); it != _location_context_vector.end(); it++) {
		config_uri = it->GetLocationUri().GetUri();
		std::string	prefix_check = _request_uri.substr(0, config_uri.size());
		if (prefix_check.compare(config_uri) == 0)
			_compatible_locationblocks.push_back(*it);
	}
}

LocationContext	LocationSelection::GetLocationContext() const {
	return _chosen_location_context;
}

void		LocationSelection::GetLongestMatch() {
	std::string		config_uri;
	LocationContext	tmp;
	size_t			longest_match = 0;
	
	for (std::vector<LocationContext>::const_iterator it = _compatible_locationblocks.begin(); it != _compatible_locationblocks.end(); it++) {
		size_t		match_size = 0;
		config_uri = it->GetLocationUri().GetUri();

		for (size_t i = 0; i < config_uri.size(); i++) {
			if (config_uri[i] == _request_uri[i])
				match_size++;
			if (match_size > longest_match)
				tmp = *it;
		}
	}
	_chosen_location_context = tmp;
}

void		LocationSelection::PrintLocationContext(std::vector<LocationContext> location_context) const {
	std::string config_uri;
	for (std::vector<LocationContext>::const_iterator it = location_context.begin(); it != location_context.end(); it++) {
		config_uri = it->GetLocationUri().GetUri();
		std::cout << config_uri << std::endl;
	}
}