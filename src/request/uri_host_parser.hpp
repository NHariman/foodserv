#ifndef URI_HOST_PARSER_HPP
#define URI_HOST_PARSER_HPP

#include <algorithm> // count
#include "astate_parser.hpp"
#include "../err/exception.hpp"
#include "../utils/request_utils.hpp"
#include "../utils/utils.hpp"

using namespace std;

class URI;

enum HostState {
	h_Start = 0,
	h_Literal,
	h_IPv6,
	h_IPvF,
	h_IPv4,
	h_LiteralEnd,
	h_RegName,
	h_RegNamePct,
	h_RegNamePctDone,
	h_Port,
	h_Done,
	h_Invalid
};

// Parses host URI string into uri_host string which it receives as a reference.
// Does not accept comma-delimited list of multiple hosts - split string first
// before passing to parser.

class URIHostParser : public AStateParser<HostState> {
	public:
		// Default constructor
		URIHostParser();
		// Destructor
		~URIHostParser();

		size_t	Parse(URI& uri, string const& input);

	private:
		URI		*_uri;
		size_t	_groups; // for counting groups of IPv4 sequences
		size_t	_colons; // for keeping track of colons for IPv6
		size_t	_digits; // for keeping track of number of digits per group
		bool	_literal;

		HostState	StartHandler(size_t pos);
		HostState	LiteralHandler(size_t pos);
		HostState	LiteralEndHandler(size_t pos);
		HostState	IPv6Handler(size_t pos);
		HostState	IPvFHandler(size_t pos);
		HostState	IPv4Handler(size_t pos);
		HostState	RegNameHandler(size_t pos);
		HostState	RegNamePctHandler(size_t pos);
		HostState	RegNamePctDoneHandler(size_t pos);
		HostState	PortHandler(size_t pos);
		HostState	PushBuffer(string& field, HostState next_state);

	protected:
		HostState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;
		void		AfterParseCheck() override;

};

#endif /* URI_HOST_PARSER_HPP */
