#include "header_field_parser.hpp"

HeaderFieldParser::HeaderFieldParser()
	: _skip_buffer(false) {}

HeaderFieldParser::~HeaderFieldParser() {}

// static FieldState FieldTransitions[5][8] = {
// 	//	WS			:			TCh			VCh			\r			\n			\0			Other
// 	{	f_Invalid,	f_Invalid,	f_Name,		f_Invalid,	f_End,		f_Done,		f_Done,		f_Invalid	}, // Start
// 	{	f_Invalid,	f_Value,	f_Name,		f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid	}, // Name
// 	{	f_Value,	f_Value,	f_Value,	f_Value,	f_End,		f_Done,		f_Done,		f_Invalid	}, // Value
// 	{	f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid,	f_Invalid,	f_Done,		f_Invalid,	f_Invalid	} // End

void	HeaderFieldParser::Parse(map<string, string>& fields, string const& field_string) {
	// _fields = &fields;
	ParseString(field_string);
	fields[_cur_field] = buffer;
}

FieldState	HeaderFieldParser::SetStartState() const {
	return f_Start;
}

FieldState	HeaderFieldParser::GetNextState(size_t pos) {
	static 	FieldState (HeaderFieldParser::*table[5])(char c) = {
			&HeaderFieldParser::StartHandler,
			&HeaderFieldParser::NameHandler,
			&HeaderFieldParser::ValueHandler,
			&HeaderFieldParser::ValueEndHandler,
			nullptr
	};

	return (this->*table[cur_state])(input[pos]);
}

void	HeaderFieldParser::InvalidStateCheck() const {
	if (cur_state == f_Invalid)
		throw BadRequestException();
}

bool	HeaderFieldParser::DoneStateCheck() {
	if (cur_state == f_Done) {
		// (*_fields)[_cur_field] = buffer;
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

FieldState	HeaderFieldParser::StartHandler(char c) {
	switch (c) {
		case '\0': case '\n':
			return f_Done;
		case '\r': {
			_skip_buffer = true;
			return f_End;
		}
		default:
			if (IsTChar(c))
				return f_Name;
			else
				return f_Invalid;
	}
}

FieldState	HeaderFieldParser::NameHandler(char c) {
	switch (c) {
		case ':': {
			_cur_field = buffer;
			buffer.clear();
			return f_Value;
		}
		default:
			if (IsTChar(c))
				return f_Name;
			else
				return f_Invalid;
	}
}

FieldState	HeaderFieldParser::ValueHandler(char c) {
	_skip_buffer = false;
	switch (c) {
		case '\0': case '\n':
			return f_Done;
		case '\r': {
			_skip_buffer = true;
			return f_End;
		}
		default:
			if (IsVChar(c))
				return f_Value;
			else if (IsWhitespace(c)) {
				_skip_buffer = true;
				return f_Value; 
			}
			else
				return f_Invalid;
	}
}

FieldState	HeaderFieldParser::ValueEndHandler(char c) {
	if (c =='\n')
		return f_Done;
	else
		return f_Invalid;
}
