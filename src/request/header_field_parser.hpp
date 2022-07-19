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
	f_ValueEnd,
	f_Done,
	f_Invalid
};

class HeaderFieldParser : public StateParser<FieldState> {
	public:
		// Default constructor
		HeaderFieldParser();
		// Destructor
		~HeaderFieldParser();

		void Parse(map<string, string>& fields, string const& field_string);

	protected:
		FieldState	SetStartState() const override;
		FieldState	GetNextState(size_t pos) override;
		void	InvalidStateCheck() const override;
		bool	DoneStateCheck() override;
		void	UpdateBuffer(size_t pos) override;
		void	IncrementCounter(size_t& pos) override;

	private:
		// size_t	_fields_bytes_read;
		map<string,string>	*_fields;
		string	_cur_field;
		bool	_skip_buffer;

		// FieldInput	GetTokenType(char c);
		FieldState	StartHandler(char c);
		FieldState	NameHandler(char c);
		FieldState	ValueStartHandler(char c);
		FieldState	ValueHandler(char c);
		FieldState	ValueEndHandler(char c);
		void		PushFieldName();
		void		PushFieldValue();
};

#endif /* HEADER_FIELD_PARSER_HPP */
