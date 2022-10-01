// https://www.journaldev.com/26342/nginx-location-directive
// on /test vs /test/
// still don't know WHY the first slash is needed
// because running the nginx file parsing test says its okay
// to just have it completely without
// look into that? maybe just make the forward slash a requirement

// probably needs an is_directory bool.

#ifndef LOCATION_URI_HPP
# define LOCATION_URI_HPP

#include <string>
#include <iostream>
#include "../../utils/config_utils.hpp"
#include "../../request/uri.hpp"

class LocationUri {
	private:
		URI			 _uri;
		bool		_is_directory;

	public:
		LocationUri();
		LocationUri(std::string input);
		~LocationUri(){};
		LocationUri(LocationUri const &obj);
		LocationUri&   operator= (LocationUri const &obj);

		std::string	GetUri() const;
		URI			GetURIClass() const;
		std::string GetInputURI() const;
		bool		IsDir() const;
		class BadUriException : public std::exception
		{
			private:
				std::string _err_string;
			public:
				BadUriException(std::string uri) {
					_err_string = "ERROR! Bad uri notation in location block: " + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~BadUriException() throw() {}
		};
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! No uri in location block.";
				}
		};
};

std::ostream&		operator<<(std::ostream& os, const LocationUri& obj);


#endif
