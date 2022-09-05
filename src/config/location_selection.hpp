#ifndef LOCANTION_SELECTION
# define LOCANTION_SELECTION

#include "location_context.hpp"


/*
    // ServerSelection selected_servercontext(host, port, config);
   	// LocationSeleccion location(selected_servercontext, std::string request_uri)
	return -> een string met pull uri path

*/

class LocationSelection {
	private:
		std::string		_request_uri;
		ServerContext	_chosen_servercontext;

		LocationSelection();

	public:
		LocationSelection(std::string request_uri);
		std::string	getRequestUri() const;
		LocationContext getLocationContext() const;

		// function to print what is in the location Context

};

#endif
