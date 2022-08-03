#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <string>

#include "exception.hpp"
#include "header_field_parser.hpp"
#include "header_field_validator.hpp"
#include "state_parser.hpp"
#include "request_line_parser.hpp"
#include "request_utils.hpp"
#include "request.hpp"

using namespace std;

class Request;

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

class RequestParser  : public StateParser<RequestState> {
	public:
		// Default constructor
		RequestParser();
		// Destructor
		~RequestParser();

		size_t		Parse(Request& request, char const* buffer);

	private:
		RequestLineParser		_request_line_parser;
		HeaderFieldParser		_header_parser;
		// HeaderFieldValidator	_header_validator;
		
		Request*	_request;
		size_t		_bytes_read;

		RequestState	RequestLineHandler(size_t pos);
		RequestState	HeaderFieldHandler(size_t pos);
		RequestState	HeaderDoneHandler(size_t pos);

	protected:
		RequestState	GetNextState(size_t pos) override;
		void			CheckInvalidState() const override;
		bool			CheckDoneState() override;
		void			IncrementCounter(size_t& pos) override;
		void			PreParseCheck() override;
		void			AfterParseCheck(size_t& pos) override;
};

#endif /* REQUESTPARSER_HPP */
