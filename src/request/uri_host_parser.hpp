#ifndef URI_HOST_PARSER_HPP
#define URI_HOST_PARSER_HPP

#include <algorithm> // count
#include "exception.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"

using namespace std;

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

class URIHostParser : public StateParser<HostState> {
	public:
		// Default constructor
		URIHostParser();
		// Destructor
		~URIHostParser();

		size_t	Parse(string& uri_host, string const& input);

	private:
		string	*_uri_host;
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

	protected:
		HostState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;
		bool		CheckDoneState() override;
		void		AfterParseCheck(size_t& pos) override;

};

#endif /* URI_HOST_PARSER_HPP */
