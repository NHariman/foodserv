#ifndef LOCANTION_SELECTION
# define LOCANTION_SELECTION

#include "location_context.hpp"
#include "server_context.hpp"
#include "directive_validation/location_uri.hpp"

/*
    // ServerSelection selected_servercontext(host, port, config);
   	// LocationSeleccion location(selected_servercontext, std::string request_uri)
	return -> een string met pull uri path

*/

class LocationSelection {
	private:
		const std::string				_request_uri;
		const ServerContext				_server_context;
		std::vector<LocationContext>	_location_context;
		LocationUri						_location_uri;
		std::string						_final_uri;
		bool							_cgi_bool;

		LocationSelection();

	public:
		LocationSelection(ServerContext chosen_servercontext, std::string request_uri);
		
		// return final request uri stuff
		std::string		getRequestUri() const;
		LocationContext getLocationContext() const;

		bool	isCgi() const;
		
		// function to print what is in the location Context
		void	PrintLocationContext() const;
};

#endif
