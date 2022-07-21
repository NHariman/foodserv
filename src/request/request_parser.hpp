#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <map>
#include <string>

#include "exception.hpp"
#include "header_field_parser.hpp"
#include "state_parser.hpp"
#include "uri.hpp"
#include "request_line_parser.hpp"
#include "request_utils.hpp"

// returned by GetHeaderFieldValue when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

using namespace std;

enum RequestState {
	// r_Start = 0,
	r_RequestLine = 0,
	r_HeaderField,
	r_HeaderDone,
	r_MsgBody,
	r_Chunked,
	r_Done,
	r_Invalid
};

// enum RequestState {
// 	r_Start = 0,
// 	r_Method,
// 	r_Target,
// 	r_Version,
// 	r_Version_Done,
// 	r_Field,
// 	r_Header_Done,
// 	r_MsgBody,
// 	r_Done,
// 	r_Invalid
// };
// #include <vector>

class RequestParser  : public StateParser<RequestState> {
	public:
		// Default constructor
		RequestParser();
		// C-string constructor
		explicit RequestParser(char const* buffer);
		// Destructor
		~RequestParser();

		void	Parse(char const* buffer);
		string	GetMethod();
		string	GetTarget();
		string	GetVersion();
		string	GetHeaderFieldValue(string field_name);
		string	GetMessageBody();

	private:
		map<string, string>	_header_fields;
		HeaderFieldParser	_header_parser;
		RequestLineParser	_request_line_parser;
		struct RequestLine	_request_line;
		
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
