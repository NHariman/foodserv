#include "uri_state_parser.hpp"

URIStateParser::URIStateParser(URI& uri) : _uri(&uri) {
	Parse(uri.GetInputURI());
}

URIStateParser::~URIStateParser() {}

void	URIStateParser::Parse(string const& uri_string) {
	static URIState (URIStateParser::*uri_jumptable[10])(char uri_char) = {
			&URIStateParser::StartHandler,
			&URIStateParser::PathHandler,
			&URIStateParser::PercentHandler,
			&URIStateParser::PercentH1Handler,
			&URIStateParser::PercentH2Handler,
			&URIStateParser::QueryHandler,
			&URIStateParser::QPercentHandler,
			&URIStateParser::QPercentH1Handler,
			&URIStateParser::QPercentH2Handler,
			nullptr
	};

	if (uri_string.size() > 8190)
		throw URITooLongException();

	enum URIState state = kStart;
	for (size_t i = 0; i < uri_string.size(); i++) {
		state = (this->*uri_jumptable[state])(uri_string[i]);
		if (state == kInvalid)
			throw BadRequestException();
		else if (state == kDone)
			break;
		// TODO: check if need to throw when finish state is indicated but still characters in string
	}
	_uri->SetPath(_path);
	_uri->SetQuery(_query);
}

URIState		URIStateParser::StartHandler(char uri_char) {
	if (uri_char == '/') {
		_path += uri_char;
		return kPath;
	}
	return kInvalid;
}

URIState		URIStateParser::PathHandler(char uri_char) {
	if (uri_char == '\0')
		return kDone;
	else if (uri_char == '%') {
		_path += uri_char;
		return kPercent;
	}
	else if (uri_char == '?') {
		_query += uri_char;
		return kQuery;
	}
	else if (uri_char == '/' && _path.back() != '/') {
		_path += uri_char;
		return kPath;
	}
	else if (IsPChar(uri_char)) {
		_path += uri_char;
		return kPath;
	}
	return kInvalid;
}

URIState		URIStateParser::PercentHandler(char uri_char) {
	if (IsHexDig(uri_char)) {
		_path += uri_char;
		return kPercent_H1;
	}
	return kInvalid;
}

URIState		URIStateParser::PercentH1Handler(char uri_char) {
	if (IsHexDig(uri_char)) {
		_path += uri_char;
		return kPercent_H2;
	}
	return kInvalid;
}

URIState		URIStateParser::PercentH2Handler(char uri_char) {
	if (uri_char == '\0')
		return kDone;
	else if (uri_char == '%') {
		_path += uri_char;
		return kPercent;
	}
	else if (uri_char == '?') {
		_query += uri_char;
		return kQuery;
	}
	else if (uri_char == '/') {
		_path += uri_char;
		return kPath;
	}
	else if (IsPChar(uri_char)) {
		_path += uri_char;
		return kPath;
	}
	return kInvalid;
}

URIState		URIStateParser::QueryHandler(char uri_char) {
	if (uri_char == '#' || uri_char == '\0')
		return kDone;
	else if (uri_char == '%') {
		_query += uri_char;
		return kQPercent;
	}
	else if (uri_char == '/' || uri_char == '?' || IsPChar(uri_char)) {
		_query += uri_char;
		return kQuery;
	}
	return kInvalid;
}

URIState		URIStateParser::QPercentHandler(char uri_char) {
	if (IsHexDig(uri_char)) {
		_query += uri_char;
		return kQPercent_H1;
	}
	return kInvalid;
}

URIState		URIStateParser::QPercentH1Handler(char uri_char) {
	if (IsHexDig(uri_char)) {
		_query += uri_char;
		return kQPercent_H2;
	}
	return kInvalid;
}

URIState		URIStateParser::QPercentH2Handler(char uri_char) {
	if (uri_char == '\0')
		return kDone;
	else if (uri_char == '%') {
		_query += uri_char;
		return kQPercent;
	}
	else if (uri_char == '?') {
		_query += uri_char;
		return kQuery;
	}
	else if (uri_char == '/') {
		_query += uri_char;
		return kQuery;
	}
	else if (IsPChar(uri_char)) {
		_query += uri_char;
		return kQuery;
	}
	return kInvalid;
}


