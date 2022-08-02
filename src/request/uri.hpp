#ifndef URI_HPP
#define URI_HPP

#include <iostream>

#include "exception.hpp"
#include "request_target_parser.hpp"
#include "uri_host_parser.hpp"

using namespace std;

// Constructs a URI object composed of: scheme, host, path, query.
// Parses during construction using RequestTargetParser, which throws
// BadRequestException if an invalid URI is passed.

class URI {
	public:
		// Default constructor
		URI();
		// Copy constructor
		URI(URI const& other);
		// String constructor
		explicit URI(string const& input);
		// Assignment operator
		URI&	operator=(URI const& other);
		// Overloaded assignment operator taking string
		URI&	operator=(string const& input);
		// Destructor
		~URI();

		string	Get() const;
		string	GetInputURI() const;
		string	GetParsedURI() const;
		string	GetURIDebug() const;
		string	GetHost() const;
		string	GetPath() const;
		string	GetQuery() const;
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
