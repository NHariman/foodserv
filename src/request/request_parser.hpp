#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <iostream>
#include <string>
#include <map>

#include "exception.hpp"
#include "request_utils.hpp"
#include "state_parser.hpp"
#include "uri.hpp"

using namespace std;

enum RequestState {
	r_Start = 0,
	r_Method,
	r_Target,
	r_Version,
	r_FieldName,
	r_FieldValue,
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
		~RequestParser();

		void	Init(char const* buffer);
		// void	ParseRequest(char const* buffer);
		string	GetMethod();
		string	GetTarget();
		string	GetVersion();
		string	GetMessageBody();

	private:
		struct RequestLine _request_line;
		string	_msg_body;
		size_t	_bytes_read;

		size_t	ParseRequestLine(string const& message);
		size_t	ParseMethod(string const& message);
		size_t	ParseTarget(string const& message, size_t start);
		RequestState StartHandler(char uri_char);
		RequestState MethodHandler(char uri_char);
		RequestState TargetHandler(char uri_char);
		RequestState VersionHandler(char uri_char);
		RequestState FieldNameHandler(char uri_char);
		RequestState FieldValueHandler(char uri_char);

	protected:
		RequestState	SetStartState() const;
		RequestState	GetNextState(char c);
		void			InvalidStateCheck() const;
		bool			DoneStateCheck();
		void			PreParseCheck() const;
		void			AfterParseCheck(size_t pos) const;
};

#endif /* REQUESTPARSER_HPP */
