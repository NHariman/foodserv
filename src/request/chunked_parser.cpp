#include "chunked_parser.hpp"

// List of header fields not allowed in chunk trailer as outlined in
// RFC 7230 Section 4.1.2.
const vector<string>	ChunkedParser::illegal_fields = {
	"Age",
	"Authorization",
	"Cache-Control",
	"Content-Encoding",
	"Content-Length",
	"Content-Range",
	"Content-Type",
	"Date",
	"Expect",
	"Expires",
	"Host",
	"Host",
	"Location",
	"Max-Forwards",
	"Pragma",
	"Proxy-Authenticate",
	"Proxy-Authorization",
	"Range",
	"Retry-After",
	"TE",
	"Trailer",
	"Vary",
	"Warning",
	"WWW-Authenticate",
	"Transfer-Encoding" };

// Default constructor
ChunkedParser::ChunkedParser()
	: StateParser(c_Start), _request(NULL), _size(0) {}

// Destructor
ChunkedParser::~ChunkedParser() {}

// Initializes pointer to Request and 
// calls on parent class StateParser::ParseString().
size_t	ChunkedParser::Parse(Request& request, string const& input) {
	_request = &request;

	return ParseString(input);
}

// Retrieves next state based on current state & character.
ChunkState	ChunkedParser::GetNextState(size_t pos) {
	static 	ChunkState (ChunkedParser::*table[])(char c) = {
			&ChunkedParser::StartHandler,
			&ChunkedParser::SizeHandler,
			&ChunkedParser::DataHandler,
			&ChunkedParser::LastHandler,
			&ChunkedParser::TrailerHandler,
			&ChunkedParser::LineEndingHandler,
			nullptr
	};

	skip_char = false;
	return (this->*table[cur_state])(input[pos]);
}

void	ChunkedParser::CheckInvalidState() const {
	if (cur_state == c_Invalid)
		throw BadRequestException("Invalid token in chunked message: \"" + buffer + "\"");
}

bool	ChunkedParser::CheckDoneState() {
	return (cur_state == c_Done);
}

ChunkState	ChunkedParser::StartHandler(char c) {
	if (IsHexDig(c))
		return c_Data;
	else
		return c_Invalid;
}

static ChunkState	HandleCRLF(bool& skip_char, ChunkState& save_state,
								ChunkState last_state) {
	skip_char = true;
	save_state = last_state;
	return c_LineEnding;
}

ChunkState	ChunkedParser::SizeHandler(char c) {
	switch (c) {
		case '\r':
			return HandleCRLF(skip_char, _save_state, c_Size);
		case '\n':
			SaveParsedValue(c_Size);
			return c_Data;
		case ';':
			skip_char = true;
			return c_Size;
		case '0':
			skip_char = true;
			return c_Last;
		default:
			return c_Invalid;
	}
}

ChunkState	ChunkedParser::DataHandler(char c) {
	switch (c) {
		case '\r':

		case '\n':
			if (_size == 0)
				return c_Size;
			else {
				SaveParsedValue(c_Data);
				return c_Data;
			}
		// decrement _size when processing data
		default:
			return c_Invalid;
	}
}

ChunkState	ChunkedParser::LastHandler(char c) {
	switch (c) {
		case '\r':
			return HandleCRLF(skip_char, _save_state, c_Trailer);
		case '\n':
			return c_Trailer;
		default:
			return c_Invalid;
	}
}

ChunkState	ChunkedParser::TrailerHandler(char c) {
	switch (c) {
		case '\r':
			return HandleCRLF(skip_char, _save_state, c_Trailer);
		case '\n':
			if (!buffer.empty())
				SaveParsedValue(c_Trailer);
			return c_Done;
		default:
			return c_Invalid;
	}
}

ChunkState	ChunkedParser::LineEndingHandler(char c) {
	if (c =='\n') {
		if (!buffer.empty())
			SaveParsedValue(_save_state);
		return _save_state;
	}
	else {
		buffer += '\r'; // pushes skipped \r character for error printing
		return c_Invalid;
	}
}

// Checks if trailer field is forbidden (according to RFC 7230 Section 4.1.2)
// and if not, if it is a valid header field (using HeaderFieldParser).
void	ChunkedParser::ParseTrailerHeader(map<string, string>& fields) {
	HeaderFieldParser	parser;
	size_t	field_name_end = buffer.find_first_of(':');
	string	field_name = buffer.substr(0, field_name_end);

	if (find(illegal_fields.begin(), illegal_fields.end(), field_name)
			== illegal_fields.end())
		parser.Parse(fields, buffer);
	else
		throw BadRequestException("Forbidden field in chunked message trailer");

}

void	ChunkedParser::SaveParsedValue(ChunkState cur_state) {
	switch (cur_state) {
		case c_Size:
			_size = HextoDec(buffer);
			break;
		case c_Data:
			_request->msg_body += buffer;
			break;
		case c_Trailer:
			ParseTrailerHeader(_request->header_fields);
			break;
		default:
			return ;
	}
	buffer.clear();
}
