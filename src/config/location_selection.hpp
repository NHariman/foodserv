#ifndef LOCANTION_SELECTION
# define LOCANTION_SELECTION

#include "location_context.hpp"

class LocationSelection {
	private:
		std::string		_request_uri;

		LocationSelection();

	public:
		LocationSelection(std::string request_uri);
		std::string	getRequestUri() const;
};

#endif
