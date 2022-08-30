#ifndef HEADER_FIELD_PARSER_HPP
#define HEADER_FIELD_PARSER_HPP

#include <map>
#include "exception.hpp"
#include "state_parser.hpp"
#include "request_utils.hpp"

using namespace std;

enum	FieldState {
	f_Start = 0,
	f_Name,
	f_ValueStart,
	f_Value,
	f_Done,
	f_Invalid
};

// Parses input string into header field names and values.

class HeaderFieldParser : public StateParser<FieldState> {
	public:
		// Default constructor
		HeaderFieldParser();
		// Destructor
		~HeaderFieldParser();

		size_t Parse(map<string, string>& fields, string const& input);

	protected:
		FieldState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;

	private:
		map<string,string>*	_fields;
		string				_cur_field;
		size_t				_bytes_read;

		FieldState	StartHandler(char c);
		FieldState	NameHandler(char c);
		FieldState	ValueStartHandler(char c);
		FieldState	ValueHandler(char c);
		FieldState	HandleCRLF(char c, FieldState next_state);
		void		PushFieldName();
		void		PushFieldValue();
};

#endif /* HEADER_FIELD_PARSER_HPP */
