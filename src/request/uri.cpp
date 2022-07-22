#include "uri.hpp"

// Default constructor
URI::URI() {}

// Copy constructor
URI::URI(URI const& other)
	:	_uri_input(other._uri_input),
		_uri_parsed(other._uri_parsed),
		_host(other._host),
		_path(other._path),
		_query(other._query) {}

// String constructor
URI::URI(string const& input) : _uri_input(input) {
	ParseInput();
}

// Assignment operator
URI&	URI::operator=(URI const& other) {
	if (this != &other) {
		this->_uri_input = other._uri_input;
		this->_uri_parsed = other._uri_parsed;
		this->_host = other._host;
		this->_path = other._path;
		this->_query = other._query;
	}
	return *this;
}

// Overloaded assignment operator taking a full URI string.
// Alternative to constructing with string.
URI&	URI::operator=(string const& input) {
	_host.clear();
	_path.clear();
	_query.clear();
	_uri_input = input;

	ParseInput();
	return *this;
}

// Destructor
URI::~URI() {}

// Simplified method for retrieving parsed URI string meant for external classes/users.
string	URI::Get() {
	return _uri_parsed;
}

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

string	URI::GetHost() {
	return _host;
}


string	URI::GetPath() {
	return _path;
}


string	URI::GetQuery() {
	return _query;
}

void	URI::SetHost(string const& host) {
	// TODO: call Host parser to validate?
	_host = host;
	_uri_parsed = ConstructParsedURI();
}

void	URI::SetPath(string const& path) {
	_path = path;
	_uri_parsed = ConstructParsedURI();
}

void	URI::SetQuery(string const& query) {
	_query = query;
	_uri_parsed = ConstructParsedURI();
}

// Parses origin-form URIs only (without host).
void	URI::ParseInput() {
	RequestTargetParser	parser;
	parser.Parse(*this, _uri_input);
	_uri_parsed = ConstructParsedURI();
}

string	URI::ConstructParsedURI() {
	string	uri;

	if (!_host.empty())
		uri += "//" + _host;
	if (!_path.empty())
		uri += _path;
	if (!_query.empty())
		uri += "?" + _query;
	return uri;
}
