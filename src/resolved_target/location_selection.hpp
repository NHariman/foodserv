#ifndef LOCANTION_SELECTION
# define LOCANTION_SELECTION

#include "../config/location_context.hpp"
#include "../config/server_context.hpp"
#include "../config/directive_validation/location_uri.hpp"

/*
    // ServerSelection selected_servercontext(host, port, config);
   	// LocationSeleccion location(selected_servercontext, std::string request_uri)
	return -> een string met pull uri path

*/

class LocationSelection {
	private:
		const std::string				_request_uri;
		const ServerContext				_server_context;
		std::vector<LocationContext>	_location_context_vector;
		LocationUri						_location_uri;
		LocationContext					_chosen_location_context;
		std::vector<LocationContext>	_compatible_locationblocks;

		LocationSelection();

	public:
		LocationSelection(ServerContext chosen_servercontext, std::string request_uri);
		
		LocationContext GetLocationContext() const;
		void			SelectLocationContext();
		void			GetLongestMatch();
		
		void	PrintLocationContext(std::vector<LocationContext> location_context) const;



};

#endif
