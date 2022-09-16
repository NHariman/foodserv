#include "request_utils.hpp"

// Used by RequestTargetParser & URIHostParser to check if previously-read char
// (that's been pushed to buffer) is `c`.
bool	PrecededBy(std::string const& read_buf, char c) {
	return (read_buf.back() == c);
}

// Used by RequestParser and RequestTargetParser to normalize input
// to either lower or uppercase.
void	NormalizeString(int (*convert)(int), std::string& s, size_t start) {
	std::transform(s.begin() + start, s.end(), s.begin() + start, convert);
}

// Used by BadRequestException to safely print error messages.
// Converts non-printable characters in string to percent-encoded values.
std::string EncodePercent(std::string const& s) {
    std::stringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = s.begin(); i != s.end(); ++i) {
        std::string::value_type c = (*i);
        // Keep printable characters
        if (isprint(c)) {
            escaped << c;
            continue;
        }
        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << static_cast<unsigned>(c);
        escaped << std::nouppercase;
    }
    return escaped.str();
}

// Used by RequestTargetParser and URIHostParser to decode percent-encoded values.
std::string	DecodePercent(std::string const& s) {
	size_t	percent_start = s.size() - 3;
	std::string	new_s = s.substr(0, percent_start);
	std::string	hex = s.substr(percent_start + 1, percent_start + 2);

	// Check for encoded CR and LF that might be used in response splitting.
	if (hex == "0D" || hex == "0A")
		throw BadRequestException("Bad octets found in encoded data");
	
	char	c = std::stoi(hex, nullptr, 16);
	new_s += c;
	return new_s;
} 

// Used by RequestValidator::ValidContentLength to convert max client body size
// specified in config (in mb format) to bytes.
size_t	MBToBytes(size_t size_mb) {
	return size_mb * 1048576;
}

size_t	HextoDec(std::string hex_string) {
	size_t n;

	std::istringstream(hex_string) >> std::hex >> n;
	return n;
}