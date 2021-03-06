#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <map>
#include <string>

#include "exception.hpp"
#include "header_field_parser.hpp"
#include "state_parser.hpp"
#include "request_line_parser.hpp"
#include "request_utils.hpp"

// returned by GetField when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

using namespace std;

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
		// C-string constructor
		explicit RequestParser(char const* buffer);
		// Destructor
		~RequestParser();

		size_t		Parse(char const* buffer);
		string		GetMethod() const;
		string		GetTarget() const;
		URI const&	GetURI() const;
		string		GetVersion() const;
		string		GetField(string field_name) const;
		string		GetMessageBody() const;

	private:
		RequestLineParser	_request_line_parser;
		struct RequestLine	_request_line;
		map<string, string>	_header_fields;
		HeaderFieldParser	_header_parser;
		
		string	_msg_body;
		size_t	_bytes_read;

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
