#include "uri.hpp"

/*
Tabular representation of URI parsing state transitions
Empty cell = invalid state
S0 is starting state & S3 is accepting state

________S0___S1___S2___S3_________
/       S1   
pchar   S1   S1   S2
?            S2
\0           S3   S3
*/

// Default constructor
URI::URI(){
	
}

// Copy constructor
URI::URI(URI const& other)
	:	_uri_input(other._uri_input),
		_uri_parsed(other._uri_parsed),
		_scheme(other._scheme),
		_host(other._host),
		_path(other._path),
		_query(other._query) {}

// String constructor
URI::URI(string const& uri_string) : _uri_input(uri_string) {
	ParseInput();
}

// Assignment operator
URI&	URI::operator=(URI const& other) {
	if (this != &other) {
		this->_uri_input = other._uri_input;
		this->_uri_parsed = other._uri_parsed;
		this->_scheme = other._scheme;
		this->_host = other._host;
		this->_path = other._path;
		this->_query = other._query;
	}
	return *this;
}

// Overloaded assignment operator taking a full URI string.
// Alternative to constructing with string.
URI&	URI::operator=(string const& uri_string) {
	_host.clear();
	_path.clear();
	_query.clear();
	_uri_input = uri_string;

	ParseInput();
	return *this;
}

// Destructor
URI::~URI() {}

string	URI::GetInputURI() {
	return _uri_input;
}

string	URI::GetParsedURI() {
	return _uri_parsed;
}

string	URI::GetURIDebug() {
	string	uri;

	if (!_host.empty())
		uri += "host: \"" + _host + "\" | ";
	if (!_path.empty())
		uri += "path: \"" + _path + "\" | ";
	if (!_query.empty())
		uri += "query: \"" + _query + "\"";
	return uri;
}

string	URI::GetScheme() {
	return _scheme;
}

string	URI::GetHost() {
	return _host;
}


string	URI::GetPath() {
	return _path;
}


string	URI::GetQuery() {
	return _query;
}


void	URI::SetScheme(string const& scheme) {
    _scheme = scheme;
}

void	URI::SetHost(string const& host) {
	_host = host;
}

void	URI::SetPath(string const& path) {
	_path = path;
}

void	URI::SetQuery(string const& query) {
	_query = query;
}

void	URI::ParseInput() {
	URIStateParser	parser(*this);
	parser.Parse(_uri_input);
	_uri_parsed = ConstructParsedURI();
}

string	URI::ConstructParsedURI() {
	string	uri;

	if (!_host.empty())
		uri += _host;
	if (!_path.empty())
		uri += _path;
	if (!_query.empty())
		uri += "?" + _query;
	return uri;
}