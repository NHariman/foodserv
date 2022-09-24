#ifndef HEADER_FIELD_PARSER_HPP
#define HEADER_FIELD_PARSER_HPP

#include <map>
#include "astate_parser.hpp"
#include "../err/exception.hpp"
#include "../utils/request_utils.hpp"
#include "../utils/utils.hpp"

class Request;

enum	FieldState {
	f_Start = 0,
	f_Name,
	f_ValueStart,
	f_Value,
	f_Done,
	f_Invalid
};

// Parses input string into header field names and values.

class HeaderFieldParser : public AStateParser<FieldState> {
	public:
		// Default constructor
		HeaderFieldParser();
		// Destructor
		~HeaderFieldParser();

		size_t Parse(Request& request, std::string const& input);

	protected:
		FieldState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;

	private:
		Request*			_request;
		std::string				_cur_field;
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
