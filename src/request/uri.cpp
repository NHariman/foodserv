#include "uri.hpp"

// Default constructor
URI::URI() {}

// Copy constructor
URI::URI(URI const& other)
	:	_uri_input(other._uri_input),
		_uri_parsed(other._uri_parsed),
		_host(other._host),
		_port(other._port),
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
		this->_port = other._port;
		this->_path = other._path;
		this->_query = other._query;
	}
	return *this;
}

// Overloaded assignment operator taking a full URI string.
// Alternative to constructing with string.
// Clears all fields before parsing new string.
URI&	URI::operator=(string const& input) {
	_host.clear();
	_port.clear();
	_path.clear();
	_query.clear();
	_uri_input = input;

	ParseInput();
	return *this;
}

// Destructor
URI::~URI() {}

// Simplified method for retrieving parsed URI string meant for external classes/users.
string	URI::Get() const {
	return _uri_parsed;
}

string	URI::GetInputURI() const {
	return _uri_input;
}

string	URI::GetParsedURI() const {
	return _uri_parsed;
}

string	URI::GetURIDebug() const {
	string	uri;

	if (!_host.empty())
		uri += "host: \"" + _host + "\" | ";
	if (!_port.empty())
		uri += "port: \"" + _port + "\" | ";
	if (!_path.empty())
		uri += "path: \"" + _path + "\" | ";
	if (!_query.empty())
		uri += "query: \"" + _query + "\"";
	return uri;
}

string	URI::GetHostWithPort() const {
	if (_port.empty())
		return _host;
	else
		return _host + ":" + _port;
}

string	URI::GetHost() const {
	return _host;
}

string	URI::GetPort() const {
	return _port;
}

string	URI::GetPath() const {
	return _path;
}


string	URI::GetQuery() const {
	return _query;
}

// Validates input string using ParseInput, which sets _host and _uri_parsed.
void	URI::SetHost(string const& host) {
	_uri_input = host;
	ParseInput();
}

// Validates input string using ParseInput, which sets _path and _uri_parsed.
void	URI::SetPath(string const& path) {
	_uri_input = path;
	ParseInput();
}

// Warning: assumes query string is correct and does not validate it.
void	URI::SetQuery(string const& query) {
	_query = query;
	_uri_parsed = ConstructParsedURI();
}

// Parses URIs using either RequestTargetParser or URIHostParser
// depending on starting character of input string.
void	URI::ParseInput() {
	size_t	slash_pos = _uri_input.find('/');

	// if no / found, assume it is host string
	if (slash_pos == string::npos) {
		URIHostParser	parser;
		parser.Parse(*this, _uri_input);
	}
	// if starts with /, assumes it is origin-form URI
	else if (slash_pos == 0) {
		RequestTargetParser	parser;
		parser.Parse(*this, _uri_input);
	}
	else
		throw BadRequestException("badly-formed URI");
	_uri_parsed = ConstructParsedURI();
}

string	URI::ConstructParsedURI() {
	string	uri;

	if (!_host.empty())
		uri += GetHostWithPort();
	if (!_path.empty())
		uri += GetPath();
	if (!_query.empty())
		uri += "?" + GetQuery();
	return uri;
}
