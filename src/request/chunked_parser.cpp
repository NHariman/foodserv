#include "chunked_parser.hpp"

#define DEBUG 0 // TODO: REMOVE

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
	: StateParser(c_Start), _request(NULL), _chunk_size(0), _chunk_ext(false) {}

// Destructor
ChunkedParser::~ChunkedParser() {}

// Initializes pointer to Request and 
// calls on parent class StateParser::ParseString().
size_t	ChunkedParser::Parse(Request& request, string const& input) {
	_request = &request;
	cout << "ChunkedParser input: " << input << endl; // DEBUG
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
			nullptr
	};
	// if (DEBUG) cout << "[CP::GetNextState] pos: " << pos << " state: " << cur_state << " in [pos]: " << input[pos] << endl; // DEBUG
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
	if (DEBUG) cout << "[StartHandler] at: [" << c << "]\n";

	if (c == '0') {
		skip_char = true;
		return c_Last;
	}
	else if (IsHexDig(c))
		return c_Size;
	else
		return c_Invalid;	
}

ChunkState	ChunkedParser::SizeHandler(char c) {
	if (DEBUG) cout << "[SizeHandler] at: [" << c << "]\n";

	switch (c) {
		case '\r':
			return HandleCRLF(c, c_Size);
		case '\n':
			_chunk_ext = false;
			return HandleCRLF(c, c_Data);
		case ';':
			skip_char = true;
			_chunk_ext = true;
			return c_Size;
		// case '0':
		// 	skip_char = true;
		// 	return c_Last;
		default:
			if (_chunk_ext == true)
				return c_Size;
			else
				return c_Invalid;
	}
}

ChunkState	ChunkedParser::DataHandler(char c) {
	if (DEBUG) cout << "[DataHandler] at: [" << c << "] | chunk size: " << _chunk_size << "\n";

	if (_chunk_size > 0)
		_chunk_size -= 1;
	switch (c) {
		case '\r':
			return HandleCRLF(c, c_Data, (_chunk_size == 0));
		case '\n':
			if (_chunk_size == 0)
				return HandleCRLF(c, c_Start);
			else
				return HandleCRLF(c, c_Data, false);
		// decrement _chunk_size when processing data
		default:
			if (IsOctet(c))
				return c_Data;
			else
				return c_Invalid;
	}
}

ChunkState	ChunkedParser::LastHandler(char c) {
	if (DEBUG) cout << "[LastHandler] at: [" << c << "]\n";

	switch (c) {
		case '\r':
			return HandleCRLF(c, c_Last);
		case '\n':
			return HandleCRLF(c, c_Trailer);
		default:
			return c_Invalid;
	}
}

ChunkState	ChunkedParser::TrailerHandler(char c) {
	if (DEBUG) cout << "[TrailerHandler] at: [" << c << "]\n";

	switch (c) {
		case '\0':
			return c_Done;
		case '\r':
			return HandleCRLF(c, c_Trailer);
		case '\n':
			return HandleCRLF(c, c_Trailer);
		default:
			return c_Trailer;
	}
}

ChunkState	ChunkedParser::HandleCRLF(char c, ChunkState next_state, bool skip) {
	static bool cr = false;

	if (cr == true && c == '\r')
		return c_Invalid;

	skip_char = skip;
	if (!buffer.empty())
		SaveParsedValue();
	cr = (c == '\r');
	return next_state;
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

void	ChunkedParser::SaveParsedValue() {
	switch (cur_state) {
		case c_Size:
			_chunk_size = HextoDec(buffer);
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

#undef DEBUG // REMOVE
