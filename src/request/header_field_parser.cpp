#include "header_field_parser.hpp"

/*
	Transition table for header field parsing
	ST = f_Start, NM = f_Name, VS = f_ValueStart, VL = f_Value,
	VE = f_ValueEnd, ✓ = f_Done, x = f_Invalid
	
		WS		:		TCh		VCh		\r		\n		\0		Other
	{	x,		x,		NM,		x,		VE,		ST,		✓,		x		}, // Start
	{	x,		VS,		NM,		x,		x,		x,		x,		x		}, // Name
	{	VS,		VL,		VL,		VL,		VL,		VL,		VL,		VL		}, // ValueStart
	{	VL,		VL,		VL,		VL,		VE,		ST,		✓,		x		}, // Value
	{	x,		x,		x,		x,		x,		ST,		x,		x		}  // ValueEnd
*/

// Default constructor
HeaderFieldParser::HeaderFieldParser()
	: StateParser(f_Start), _fields(NULL) {}

// Destructor
HeaderFieldParser::~HeaderFieldParser() {}

// Initializes pointer to Header Fields map and 
// calls on parent class StateParser::ParseString().
size_t	HeaderFieldParser::Parse(map<string, string>& fields, string const& input) {
	_fields = &fields;
	return ParseString(input);
}

// Retrieves next state based on current state & character.
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
		throw BadRequestException("Invalid token in header fields: \"" + buffer + "\"");
}

bool	HeaderFieldParser::CheckDoneState() {
	return (cur_state == f_Done);
}

// Checks if header fields size is greater than 8kb.
void	HeaderFieldParser::PreParseCheck() {
	if (input.size() > 8192)
		throw RequestHeaderFieldsTooLargeException();
}

// Header field may only start with TChar.
FieldState	HeaderFieldParser::StartHandler(char c) {
	skip_char = false;
	buffer.clear();
	switch (c) {
		case '\0':
			return f_Done;
		case '\n':
			return f_Start;
		case '\r': {
			skip_char = true;
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
			skip_char = true;
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
	skip_char = false;
	if (IsWhitespace(c)) {
		skip_char = true;
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
			skip_char = true;
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
		if (!buffer.empty())
			PushFieldValue();
		return f_Start;
	}
	else {
		buffer += '\r'; // pushes skipped \r character for error printing
		return f_Invalid;
	}
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
	buffer.clear();
}
