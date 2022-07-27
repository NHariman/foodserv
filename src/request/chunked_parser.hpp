#ifndef CHUNKED_PARSER_HPP
#define CHUNKED_PARSER_HPP

// List of header fields not allowed in chunk trailer as outlined in
// RFC 7230 Section 4.1.2.
static string[] NOT_ALLOWED_FIELDS = {
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

#endif /* CHUNKED_PARSER_HPP */
