#ifndef URI_HPP
#define URI_HPP

#include <iostream>

#include "exception.hpp"
#include "uri_state_parser.hpp"

using namespace std;

class URI {
	public:
		URI();
		URI(URI const& other);
		URI(string const& uri_string);
		URI&	operator=(URI const& other);
		URI&	operator=(string const& uri_string);
		~URI();

		string	GetInputURI();
		string	GetParsedURI();
		string	GetURIDebug();
		string	GetScheme();
		string	GetHost();
		string	GetPath();
		string	GetQuery();
		void	SetScheme(string const& scheme);
		void	SetHost(string const& host);
		void	SetPath(string const& path);
		void	SetQuery(string const& query);

	private:
		string	_uri_input;
		string	_uri_parsed;
		string	_scheme;
		string	_host;
		string	_path;
		string	_query;
};

#endif /* URI_HPP */
