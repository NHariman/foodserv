#ifndef URI_STATE_PARSER_HPP
#define URI_STATE_PARSER_HPP

#include "uri.hpp"
#include "request_utils.hpp"

using namespace std;

class URI;

enum URIState {
	kStart = 0,
	kPath,
	kPercent,
	kPercent_H1,
	kPercent_H2,
	kQuery,
	kQPercent,
	kQPercent_H1,
	kQPercent_H2,
	kDone,
	kInvalid
};

class	URIStateParser {
	public:
		URIStateParser(URI& uri);
		~URIStateParser();

	private:
		URI		*_uri;
		string	_scheme;
		string	_host;
		string	_path;
		string	_query;

		void		Parse(string const& uri_string);
		URIState	StartHandler(char uri_char);
		URIState	PathHandler(char uri_char);
		URIState	PercentHandler(char uri_char);
		URIState	PercentH1Handler(char uri_char);
		URIState	PercentH2Handler(char uri_char);
		URIState	QueryHandler(char uri_char);
		URIState	QPercentHandler(char uri_char);
		URIState	QPercentH1Handler(char uri_char);
		URIState	QPercentH2Handler(char uri_char);
};

#endif /* URI_STATE_PARSER_HPP */
