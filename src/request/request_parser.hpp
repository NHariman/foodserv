#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <algorithm> // transform
#include <map>
#include <string>
#include <vector>

#include "exception.hpp"
#include "header_field_parser.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"
#include "uri.hpp"

// returned by GetHeaderFieldValue when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

using namespace std;

enum RequestState {
	r_Start = 0,
	r_Method,
	r_Target,
	r_Version,
	r_Version_Done,
	r_Field,
	r_Header_Done,
	r_MsgBody,
	r_Done,
	r_Invalid
};

struct RequestLine {
	string	method;
	URI		target;
	string	version;
};

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
		// HeaderFieldParser	_header_parser;
		struct RequestLine	_request_line;
		
		string	_msg_body;
		size_t	_bytes_read;

		RequestState	StartHandler(size_t pos);
		RequestState	MethodHandler(size_t pos);
		// RequestState	MethodDoneHandler(size_t pos);
		RequestState	TargetHandler(size_t pos);
		// RequestState	TargetDoneHandler(size_t pos);
		RequestState	VersionHandler(size_t pos);
		RequestState	VersionDoneHandler(size_t pos);
		RequestState	FieldHandler(size_t pos);
		RequestState	HeaderDoneHandler(size_t pos);
		RequestState	ValidDelimiter(bool (*valid)(char), size_t pos); // TODO: remove if unused

	protected:
		RequestState	SetStartState() const override;
		RequestState	GetNextState(size_t pos) override;
		void			InvalidStateCheck() const override;
		bool			DoneStateCheck() override;
		// bool			NotDone(size_t pos) const;
		void			IncrementCounter(size_t& pos) override;
		void			PreParseCheck() override;
		void			AfterParseCheck(size_t pos) override;
};

#endif /* REQUESTPARSER_HPP */
