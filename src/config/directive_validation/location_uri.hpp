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

class LocationUri {
	private:
		bool		_is_empty;
		std::string _uri;
		bool		_is_directory;

	public:
		LocationUri();
		LocationUri(std::string input);
		~LocationUri(){};
		LocationUri(LocationUri &obj);
		LocationUri&   operator= (LocationUri const &obj);

		std::string	GetUri() const;
		bool		IsDirectory() const;
		bool        IsEmpty() const;
		class BadUriException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad uri notation in location block.";
				}
		};
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! No uri in location block.";
				}
		};
};

#endif
