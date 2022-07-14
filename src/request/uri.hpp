#ifndef URI_HPP
#define URI_HPP

#include <iostream>

#include "exception.hpp"
#include "request_target_parser.hpp"
#include "uri_state_enums.hpp"

using namespace std;

// Constructs a URI object composed of: scheme, host, path, query.
// Parses during construction using RequestTargetParser, which throws
// BadRequestException if an invalid URI is passed.

class URI {
	public:
		URI();
		URI(URI const& other);
		URI(string const& uri_string);
		URI&	operator=(URI const& other);
		URI&	operator=(string const& uri_string);
		~URI();

		string	Get();
		string	GetInputURI();
		string	GetParsedURI();
		string	GetURIDebug();
		string	GetHost();
		string	GetPath();
		string	GetQuery();
		void	SetHost(string const& host);
		void	SetPath(string const& path);
		void	SetQuery(string const& query);

	private:
		string	_uri_input;
		string	_uri_parsed;
		string	_host;
		string	_path;
		string	_query;

		void	ParseInput();
		string	ConstructParsedURI();
};

#endif /* URI_HPP */
