#ifndef REQUEST_TARGET_PARSER_HPP
#define REQUEST_TARGET_PARSER_HPP

#include "uri.hpp"
#include "uri_state_enums.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"

using namespace std;

class URI;

class	RequestTargetParser : public StateParser<URIState> {
	public:
		// URI constructor
		RequestTargetParser(URI& uri);
		~RequestTargetParser();


		void	Parse(string const& uri_string);

	private:
		URI		*_uri;
		URIPart _part;

		// void		ParseHost(string const& uri_string); // TODO: review later if should be moved
		// void		ParsePathOriginForm(string const& uri_string);
		void		PushBuffertoField(URIPart part);
		URIState	StartHandler(char uri_char);
		URIState	PathHandler(char uri_char);
		URIState	QueryHandler(char uri_char);
		URIState	PercentHandler(char uri_char);
		URIState	PercentDoneHandler(char uri_char);
	
	protected:
		URIState	SetStartState() const;
		URIState	GetNextState(size_t pos);
		void		InvalidStateCheck() const;
		bool		DoneStateCheck();
		void		PreParseCheck();
		void		AfterParseCheck(size_t pos);
};

#endif /* REQUEST_TARGET_PARSER_HPP */
