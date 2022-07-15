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
	f_Value,
	f_End,
	f_Done,
	f_Invalid
};

// enum	FieldInput {
// 	f_Whitespace,
// 	f_Colon,
// 	f_TChar,
// 	f_VChar,
// 	f_CR,
// 	f_NL,
// 	f_EOL,
// 	f_Other
// };

class HeaderFieldParser : public StateParser<FieldState> {
	public:
		// Default constructor
		HeaderFieldParser();
		// Destructor
		~HeaderFieldParser();

		void Parse(map<string, string>& fields, string const& field_string);

	protected:
		FieldState	SetStartState() const;
		FieldState	GetNextState(size_t pos);
		void	InvalidStateCheck() const;
		bool	DoneStateCheck();
		void	UpdateBuffer(size_t pos);
		void	IncrementCounter(size_t& pos);

	private:
		// size_t	_fields_bytes_read;
		// map<string,string>	*_fields;
		string	_cur_field;
		bool	_skip_buffer;

		// FieldInput	GetTokenType(char c);
		FieldState	StartHandler(char c);
		FieldState	NameHandler(char c);
		FieldState	ValueHandler(char c);
		FieldState	ValueEndHandler(char c);
};

#endif /* HEADER_FIELD_PARSER_HPP */
