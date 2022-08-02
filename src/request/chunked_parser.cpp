#include "chunked_parser.hpp"

// List of header fields not allowed in chunk trailer as outlined in
// RFC 7230 Section 4.1.2.
const string	ChunkedParser::illegal_fields[25] = {
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

