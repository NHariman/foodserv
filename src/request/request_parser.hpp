#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "exception.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"
#include "uri.hpp"

// returned by GetHeaderFieldValue when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

using namespace std;

enum RequestState {
	r_Start = 0,
	r_Method,
	r_Method_Done,
	r_Target,
	r_Target_Done,
	r_Version,
	r_Version_Done,
	r_FieldName,
	r_FieldValue,
	r_FieldDone,
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
		RequestParser();
		// char array constructor
		RequestParser(char const* buffer);
		~RequestParser();

		void	Parse(char const* buffer);
		string	GetMethod();
		string	GetTarget();
		string	GetVersion();
		string	GetHeaderFieldValue(string field_name);
		string	GetMessageBody();

	private:
		struct RequestLine	_request_line;
		map<string, string>	_header_fields;
		string	_msg_body;
		size_t	_bytes_read;
		size_t	_header_fields_size;

		RequestState	StartHandler(size_t pos);
		RequestState	MethodHandler(size_t pos);
		RequestState	MethodDoneHandler(size_t pos);
		RequestState	TargetHandler(size_t pos);
		RequestState	TargetDoneHandler(size_t pos);
		RequestState	VersionHandler(size_t pos);
		RequestState	VersionDoneHandler(size_t pos);
		RequestState	FieldNameHandler(size_t pos);
		// RequestState	FieldValueHandler(size_t pos);
		RequestState	ValidDelimiter(bool (*valid)(char), size_t pos);

	protected:
		RequestState	SetStartState() const;
		RequestState	GetNextState(size_t pos);
		void			InvalidStateCheck() const;
		bool			DoneStateCheck();
		// bool			NotDone(size_t pos) const;
		void			IncrementCounter(size_t& pos);
		void			PreParseCheck();
		void			AfterParseCheck(size_t pos);
};

#endif /* REQUESTPARSER_HPP */
