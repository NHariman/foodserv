#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <string>
#include "chunked_parser.hpp"
#include "exception.hpp"
#include "header_field_parser.hpp"
#include "request_validator.hpp"
#include "astate_parser.hpp"
#include "request_line_parser.hpp"
#include "request_utils.hpp"

using namespace std;

class Request;
class RequestValidator;
class NginxConfig;

enum RequestState {
	r_RequestLine = 0,
	r_HeaderField,
	r_HeaderDone,
	r_MsgBody,
	r_Chunked,
	r_Done,
	r_Invalid
};

// Parses and validates request header components, i.e. request method,
// request target, HTTP version, header fields, message body.

class RequestParser  : public AStateParser<RequestState> {
	public:
		// Default constructor
		RequestParser();
		// Config constructor
		RequestParser(NginxConfig *config);
		// Destructor
		~RequestParser();

		size_t		Parse(Request& request, string const& buffer);

		// friend class forward declaration allows Request to
		// access protected `cur_state` attribute.
		friend class	Request;

	private:
		RequestLineParser		_request_line_parser;
		HeaderFieldParser		_header_parser;
		ChunkedParser			_chunked_parser;
		NginxConfig				*_config;
		
		Request		*_request;

		RequestState	RequestLineHandler();
		RequestState	HeaderFieldHandler();
		RequestState	HeaderDoneHandler();
		RequestState	MessageBodyHandler();
		RequestState	ChunkedHandler();
		void			HandleEndOfChunkedMessage();
		void			DebugPrint();

	protected:
		RequestState	GetNextState(size_t pos) override;
		void			CheckInvalidState() const override;
		void			IncrementCounter() override;
		void			PreParseCheck() override;
		void			AfterParseCheck() override;
};

#endif /* REQUESTPARSER_HPP */
