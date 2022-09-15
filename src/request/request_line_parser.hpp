#ifndef REQUEST_LINE_PARSER_HPP
#define REQUEST_LINE_PARSER_HPP

#include <string>
#include <vector>

#include "../err/exception.hpp"
#include "astate_parser.hpp"
#include "uri.hpp"
#include "../utils/utils.hpp"

struct RequestLine {
	string	method;
	URI		target;
	string	version;
};

enum RequestLineState {
	l_Start = 0,
	l_Method,
	l_Target,
	l_Version,
	l_VersionEnd,
	l_Done,
	l_Invalid
};

// Parses request line string into method, target, and version
// components of RequestLine struct to which it receives a reference.

class RequestLineParser : public AStateParser<RequestLineState> {
	public:
		// Default constructor
		RequestLineParser();
		// Destructor
		~RequestLineParser();

		size_t	Parse(RequestLine& request_line, string const& input);

	protected:
		RequestLineState	GetNextState(size_t pos) override;
		void				CheckInvalidState() const override;
		bool				CheckDoneState() override;
		void				IncrementCounter() override;

	private:
		RequestLine*	_request_line;

		RequestLineState	StartHandler();
		RequestLineState	MethodHandler();
		RequestLineState	TargetHandler();
		RequestLineState	VersionHandler();
		RequestLineState	VersionEndHandler();
		
		size_t	GetEndPos(string const& s, char to_find, size_t start);
		size_t	GetCRLFPos(string const& input, size_t pos);
};

#endif /* REQUEST_LINE_PARSER_HPP */
