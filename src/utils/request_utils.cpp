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

<<<<<<< HEAD
// Used by RequestTargetParser and URIHostParser.
// Loops through string `s` and converts any percent-encoded values (starting with %).
// Takes optional `start` parameter for position of %.
std::string	DecodePercent(std::string const& s, size_t start) {
	std::string	new_s;
	
	// if start is given, copy over any preceding characters.
	if (start > 0)
		new_s = s.substr(0, start);

	for (auto it = s.begin() + start; it < s.end(); it++) {
		if (*it == '%') { // percent-encoded values are preceded by %
			std::string	hex = std::string(it + 1, it + 3);
			// Check for encoded CR and LF that might be used in response splitting.
			if (hex == "0D" || hex == "0A")
				throw BadRequestException("Bad octets found in encoded data");
			char	c = std::stoi(hex, nullptr, 16);
			new_s += c;

			it += 2; // move iterator past percent-encoded value
		}
		else
			new_s += *it;
=======
// Used by RequestTargetParser and URIHostParser to decode percent-encoded values.
std::string	DecodePercent(std::string const& s) {
	std::string	new_s;

	for (auto it = s.begin(); it != s.end(); it++) {
		if (*it != '%') {
			new_s += *it;
			continue;
		}
		else {
			
		}
	}
	size_t pct = s.find_first_of('%');
	size_t start = 0;

	for (size_t i = s[pct]; i < s.size() ; i++) {
		new_s += s.substr(start, i);
		std::string	hex = s.substr(i + 1, i + 2);

		// Check for encoded CR and LF that might be used in response splitting.
		if (hex == "0D" || hex == "0A")
			throw BadRequestException("Bad octets found in encoded data");
		
		char	c = std::stoi(hex, nullptr, 16);
		new_s += c;
		start += 
>>>>>>> d2e359518e359dd79f2f7c2916bfdb022c30ce51
	}
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
