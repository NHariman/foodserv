#ifndef URI_STATE_PARSER_HPP
#define URI_STATE_PARSER_HPP

#include "uri.hpp"
#include "uri_state_enums.hpp"
#include "request_utils.hpp"

using namespace std;

class URI;

class	URIStateParser {
	public:
		// URI constructor
		URIStateParser(URI& uri);
		~URIStateParser();

		void	Parse(string uri_string, URIPart part = pt_Path);

	private:
		URI		*_uri;
		string	_uri_input;
		string	_buffer;
		URIPart _part;

		void		ParseHost(string const& uri_string);
		void		ParsePathOriginForm(string const& uri_string);
		void		FillPathQueryFields();
		URIState	StartHandler(char uri_char);
		URIState	PathHandler(char uri_char);
		URIState	PercentHandler(char uri_char);
		URIState	PercentDoneHandler(char uri_char);
		URIState	QueryHandler(char uri_char);
};

#endif /* URI_STATE_PARSER_HPP */
