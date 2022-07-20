#include "header_field_parser.hpp"

HeaderFieldParser::HeaderFieldParser()
	: _fields(NULL), _skip_buffer(false) {}

HeaderFieldParser::~HeaderFieldParser() {}

// TODO: Remove
// static FieldState FieldTransitions[5][8] = {
// 	//	WS			:			TCh			VCh			\r				\n			\0			Other
// 	{	f_Invalid,	f_Invalid,	f_Name,		f_Invalid,	f_ValueEnd,		f_Done,		f_Done,		f_Invalid	}, // Start
// 	{	f_Invalid,	f_Value,	f_Name,		f_Invalid,	f_Invalid,		f_Invalid,	f_Invalid,	f_Invalid	}, // Name
// 	{	f_Value,	f_Value,	f_Value,	f_Value,	f_ValueEnd,		f_Done,		f_Done,		f_Invalid	}, // Value
// 	{	f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid,		f_Done,		f_Invalid,	f_Invalid	} // End

size_t	HeaderFieldParser::Parse(map<string, string>& fields, string const& field_string) {
	_fields = &fields;
	return ParseString(field_string);
}

FieldState	HeaderFieldParser::SetStartState() const {
	return f_Start;
}

FieldState	HeaderFieldParser::GetNextState(size_t pos) {
	static 	FieldState (HeaderFieldParser::*table[])(char c) = {
			&HeaderFieldParser::StartHandler,
			&HeaderFieldParser::NameHandler,
			&HeaderFieldParser::ValueStartHandler,
			&HeaderFieldParser::ValueHandler,
			&HeaderFieldParser::ValueEndHandler,
			nullptr
	};
	return (this->*table[cur_state])(input[pos]);
}

void	HeaderFieldParser::CheckInvalidState() const {
	if (cur_state == f_Invalid)
		throw BadRequestException();
}

bool	HeaderFieldParser::CheckDoneState() {
	if (cur_state == f_Done) {
		return true;
	}
	return false;
}

void	HeaderFieldParser::UpdateBuffer(size_t pos) {
	if (!_skip_buffer)
		buffer += input[pos];
}

void	HeaderFieldParser::IncrementCounter(size_t& pos) {
	pos += 1;
	if (pos == 8192 && input.size() > pos)
		throw RequestHeaderFieldsTooLargeException();
}

// Header field may only start with TChar.
FieldState	HeaderFieldParser::StartHandler(char c) {
	_skip_buffer = false;
	buffer.clear();
	switch (c) {
		case '\0':
			return f_Done;
		case '\n':
			return f_Start;
		case '\r': {
			_skip_buffer = true;
			return f_ValueEnd;
		}
		default:
			if (IsTChar(c))
				return f_Name;
			else
				return f_Invalid;
	}
}

// Header field name may only be TChar with no whitespace before the ':'
// signaling transition to field value.
FieldState	HeaderFieldParser::NameHandler(char c) {
	switch (c) {
		case ':': {
			PushFieldName();
			_skip_buffer = true;
			return f_ValueStart;
		}
		default:
			if (IsTChar(c))
				return f_Name;
			else
				return f_Invalid;
	}
}

// Skips whitespace following colon but before value starts.
FieldState	HeaderFieldParser::ValueStartHandler(char c) {
	_skip_buffer = false;
	if (IsWhitespace(c)) {
		_skip_buffer = true;
		return f_ValueStart;
	}
	else
		return f_Value;
}

// Accepts VChar or whitespace for field value. If \r found,
// returns ValueEnd state to check for valid CRLF sequence.
FieldState	HeaderFieldParser::ValueHandler(char c) {
	switch (c) {
		case '\0': {
			PushFieldValue();
			return f_Done;
		}
		case '\n': {
			PushFieldValue();
			return f_Start;
		}
		case '\r': {
			_skip_buffer = true;
			return f_ValueEnd;
		}
		default:
			if (IsVChar(c) || IsWhitespace(c))
				return f_Value;
			else
				return f_Invalid;
	}
}

// Checks if \r is followed by \n for valid CRLF line ending.
FieldState	HeaderFieldParser::ValueEndHandler(char c) {
	if (c =='\n') {
		PushFieldValue();
		return f_Start;
	}
	else
		return f_Invalid;
}

// Normalizes field name to lowercase (for easy look-up)
// and saves buffer to `cur_field` for use once value is parsed.
void	HeaderFieldParser::PushFieldName() {
	NormalizeString(tolower, buffer, 0);
	_cur_field = buffer;
	buffer.clear();
}

// Trims trailing whitespace off field value and saves buffer
// as value of cur_field key in `fields` map that was passed in Parse().
void	HeaderFieldParser::PushFieldValue() {
	string::iterator	start = buffer.begin();
	string::iterator	end = buffer.end() - 1;

	while (start != end && IsWhitespace(*end))
		end--;
	(*_fields)[_cur_field] = string(start, end + 1);
}
