#include "chunked_parser.hpp"
#include "header_field_parser.hpp"
#include "../request.hpp"

// List of header fields not allowed in chunk trailer as outlined in
// RFC 7230 Section 4.1.2.
const std::vector<std::string>	ChunkedParser::illegal_fields = {
	"Authorization",
	"Cache-Control",
	"Content-Encoding",
	"Content-Length",
	"Content-Range",
	"Content-Type",
	"Cookie",
	"Expect",
	"Host",
	"If-Match",
	"If-None-Match",
	"If-Modified-Since",
	"If-Unmodified-Since",
	"If-Range",
	"Max-Forwards",
	"Pragma",
	"Proxy-Authenticate",
	"Proxy-Authorization",
	"Range",
	"Set-Cookie",
	"TE",
	"Trailer",
	"Transfer-Encoding"
	"WWW-Authenticate" };

// Default constructor
ChunkedParser::ChunkedParser()
	:	AStateParser(c_Start, c_Done), _request(NULL), _chunk_size(0), _chunk_ext_size(0),
		_chunk_ext(false), _chunk_trailer(false), _cr(false) {}

// Destructor
ChunkedParser::~ChunkedParser() {}

// Initializes pointer to Request and 
// calls on parent class AStateParser::ParseString().
size_t	ChunkedParser::Parse(Request& request, std::string const& input) {
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
			&ChunkedParser::EndHandler,
			nullptr
	};
	skip_char = false;

	return (this->*table[cur_state])(input[pos]);
}

void	ChunkedParser::CheckInvalidState() const {
	if (cur_state == c_Invalid)
		throw BadRequestException("Invalid token in chunked message: \"" + buffer + "\"");
}

void	ChunkedParser::AfterParseCheck() {
	if (cur_state == c_Done && _chunk_size != 0)
		throw BadRequestException("Missing chunk in message");
}

// Handles transition on start of parsing and of new lines when
// chunk data has been fully read.
ChunkState	ChunkedParser::StartHandler(char c) {
	if (c == '0') {
		skip_char = true;
		return c_Last;
	}
	else if (c == '\0')
		return c_Start;
	else if (IsHexDig(c))
		return c_Size;
	else
		return c_Invalid;
}

// Handles parsing of chunk size, ignoring chunk-extensions.
// Checks for overly-lengthy chunk sizes and chunk extensions.
// Limit for chunk extension follows 8kb limit of URI & header fields.
// Limit for chunk size is based on 1,048,576B limit for payload.
ChunkState	ChunkedParser::SizeHandler(char c) {
	// chunk size & chunk extension size check
	if (buffer.size() > 7)
		throw PayloadTooLargeException();
	if (_chunk_ext == true) {
		if (_chunk_ext_size > MAX_CHUNKEXT_SIZE)
			throw PayloadTooLargeException();
		else
			return HandleChunkExtension(c);
	}
	switch (c) {
		case '\0':
			skip_char = true;
			return c_Size;
		case '\r':
			return HandleCRLF(c, c_Size);
		case '\n':
			return HandleCRLF(c, c_Data);
		case ';':
			skip_char = true;
			_chunk_ext = true;
			return c_Size;
		default:
			if (isdigit(c))
				return c_Size;
			else
				return c_Invalid;
	}
}

// Handles parsing of chunk data, reading octets as data until
// previously-indicated chunk size has been met.
ChunkState	ChunkedParser::DataHandler(char c) {
	if (_request->GetMessageBody().size() + _chunk_size > _request->max_body_size)
		throw PayloadTooLargeException();
	if (_chunk_size > 0)
		_chunk_size -= 1;
	switch (c) {
		case '\0':
			skip_char = true;
			return c_Data;
		case '\r':
			return HandleCRLF(c, c_Data, (_chunk_size == 0));
		case '\n':
			if (_chunk_size == 0)
				return HandleCRLF(c, c_Start);
			else
				return HandleCRLF(c, c_Data, false);
		default:
			if (IsOctet(c))
				return c_Data;
			else
				return c_Invalid;
	}
}

// Handles last-chunk parsing, which is '0' followed by CRLF.
// Like SizeHandler, ignores chunk extensions but guards against overly-long
// chunk extensions.
ChunkState	ChunkedParser::LastHandler(char c) {
	if (_chunk_ext == true) {
		if (_chunk_ext_size > MAX_CHUNKEXT_SIZE)
			throw PayloadTooLargeException();
		else
			return HandleChunkExtension(c);
	}
	switch (c) {
		case '\0':
			skip_char = true;
			return c_Last;
		case '\r':
			return HandleCRLF(c, c_Last);
		case '\n':
			return HandleCRLF(c, c_Trailer);
		case ';':
			skip_char = true;
			_chunk_ext = true;
			return c_Last;
		default:
			return c_Invalid;
	}
}

// Handles trailer header fields.
ChunkState	ChunkedParser::TrailerHandler(char c) {
	switch (c) {
		case '\r':
			return HandleCRLF(c, c_Trailer);
		case '\n':
			if (_chunk_trailer == true) {
				_chunk_trailer = false;
				return HandleCRLF(c, c_Trailer);
			}
			else
				return c_End;
		case '\0':
			skip_char = true;
			return c_Trailer;
		default:
			_chunk_trailer = true;
			return c_Trailer;
	}
}

// Handles empty line that must end chunked transfer coding.
ChunkState	ChunkedParser::EndHandler(char c) {
	switch (c) {
		case '\0':
			skip_char = true;
			return c_Done;
		default:
			return c_Invalid;
	}
}

// Helper function for skipping chunk extensions while checking its size.
ChunkState	ChunkedParser::HandleChunkExtension(char c) {
	if (c == '\n') {
		_chunk_ext = false;
		_chunk_ext_size = 0;
		return HandleCRLF(c, ChunkState(cur_state + 1));
	}
	skip_char = true;
	_chunk_ext_size += 1;
	return cur_state;
}

// Helper function for parsing line endings.
// Accepts both CRLF and just LF as line endings.
// `skip` is optional argument that defaults to TRUE.
// Uses bool `_cr` to remember if a CR has previously been found.
// If buffer is not empty, pushes buffer to appropriate field.
ChunkState	ChunkedParser::HandleCRLF(char c, ChunkState next_state, bool skip) {
	// Check for any sequence other than CRLF.
	if (_cr == true && c != '\n')
		return c_Invalid;

	skip_char = skip;
	if (!buffer.empty())
		SaveParsedValue();
	_cr = (c == '\r');
	return next_state;
}

// Checks if trailer field is forbidden (according to RFC 7230 Section 4.1.2)
// and if not, if it is a valid header field (using HeaderFieldParser).
void	ChunkedParser::ParseTrailerHeader() {
	HeaderFieldParser	parser;
	size_t	field_name_end = buffer.find_first_of(':');
	std::string	field_name = buffer.substr(0, field_name_end);

	if (find(illegal_fields.begin(), illegal_fields.end(), field_name)
			== illegal_fields.end())
		parser.Parse(*_request, buffer);
	else
		throw BadRequestException("Forbidden field in chunked message trailer");
}

// Pushes buffer value into appropriate field
// (chunk size, msg_body, header fields), depending on current state,
// and clears buffer.
void	ChunkedParser::SaveParsedValue() {
	switch (cur_state) {
		case c_Size:
			_chunk_size = HextoDec(buffer);
			break;
		case c_Data:
			_request->SetMessageBody(_request->GetMessageBody() + buffer);
			break;
		case c_Trailer:
			ParseTrailerHeader();
			break;
		default:
			return ;
	}
	buffer.clear();
}
