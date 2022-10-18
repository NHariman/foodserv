#include "uri.hpp"
#include "parser/request_target_parser.hpp"
#include "parser/uri_host_parser.hpp"

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
URI::URI(std::string const& input) : _uri_input(input) {
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
URI&	URI::operator=(std::string const& input) {
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
std::string const&	URI::Get() const {
	return _uri_parsed;
}

std::string const&	URI::GetInputURI() const {
	return _uri_input;
}

std::string const&	URI::GetParsedURI() const {
	return _uri_parsed;
}

std::string	URI::GetURIDebug() const {
	std::string	uri;

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

std::string	URI::GetHostWithPort() const {
	if (_port.empty())
		return _host;
	else
		return _host + ":" + _port;
}

std::string const&	URI::GetHost() const {
	return _host;
}

std::string const&	URI::GetPort() const {
	return _port;
}

std::string const&	URI::GetPath() const {
	return _path;
}


std::string const&	URI::GetQuery() const {
	return _query;
}

// Validates input string using ParseInput, which sets _host and _uri_parsed.
void	URI::SetHost(std::string const& host) {
	_uri_input = host;
	ParseInput(Part::Host);
}

// Validates input string using ParseInput, which sets _path and _uri_parsed.
void	URI::SetPath(std::string const& path) {
	_uri_input = path;
	ParseInput(Part::Path);
}

// Warning: assumes query string is correct and does not validate it.
void	URI::SetQuery(std::string const& query) {
	_query = query;
	_uri_parsed = ConstructParsedURI();
}

// Parses URIs using either RequestTargetParser or URIHostParser
// depending on starting character of input string.
// Takes optional argument `part` for specifying which parser
// should be used. Defaults to -1.
void	URI::ParseInput(URI::Part part) {
	size_t	slash_pos = _uri_input.find('/');

	// if no / found, assume it is host string
	if (part == Part::Host || slash_pos == std::string::npos) {
		URIHostParser	parser;
		parser.Parse(*this, _uri_input);
	}
	// if starts with /, assumes it is origin-form URI
	else if (part == Part::Path || slash_pos == 0) {
		RequestTargetParser	parser;
		parser.Parse(*this, _uri_input);
	}
	else
		throw BadRequestException("badly-formed URI");
	_uri_parsed = ConstructParsedURI();
}

std::string	URI::ConstructParsedURI() {
	std::string	uri;

	if (!_host.empty())
		uri += GetHostWithPort();
	if (!_path.empty())
		uri += GetPath();
	if (!_query.empty())
		uri += "?" + GetQuery();
	return uri;
}
