#ifndef REQUEST_TARGET_PARSER_HPP
#define REQUEST_TARGET_PARSER_HPP

#include "uri.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"

using namespace std;

class URI;

enum URIPart {
	pt_Invalid = -1,
	pt_Host = 0,
	pt_Path,
	pt_Query
};

enum URIState {
	u_Start = 0,
	u_Path,
	u_Query,
	u_Percent,
	u_Percent_Done,
	u_Done,
	u_Invalid
};

// Parses origin-form URI strings into path & query components of URI object.

class RequestTargetParser : public StateParser<URIState> {
	public:
		// Default constructor
		RequestTargetParser();
		// Destructor
		~RequestTargetParser();


		size_t	Parse(URI& uri, string const& input);

	private:
		URI		*_uri;
		URIPart _part;

		// void		ParseHost(string const& input); // TODO: review later if should be moved
		void		PushBuffertoField(URIPart part);
		URIState	StartHandler(char uri_char);
		URIState	PathHandler(char uri_char);
		URIState	QueryHandler(char uri_char);
		URIState	PercentHandler(char uri_char);
		URIState	PercentDoneHandler(char uri_char);
	
	protected:
		URIState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;
		bool		CheckDoneState() override;
		void		PreParseCheck() override;
		void		AfterParseCheck() override;
};

#endif /* REQUEST_TARGET_PARSER_HPP */
