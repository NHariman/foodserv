#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

#define MAX_CHUNKEXT_SIZE 8192 // used by ChunkedParser
#define MAX_HEADER_SIZE	8192 // used by HeaderFieldParser
#define MAX_URI_SIZE 8192 // used by RequestTargetParser
#define BUFFER_SIZE 8192

// file_handling.cpp
bool	IsValidFile(std::string const& path);
bool	IsValidDirectory(std::string const& path);
int 	CreateFile(std::string const& file_path, bool close_after = false);
std::string		GetLastModified(std::string const& path);
size_t			GetStreamSize(std::istream* stream);
std::istream*	CreateStreamFromString(std::string const& string_buffer);
std::istream*	CreateStreamFromPath(std::string const& file_path);

// is_functions.cpp
bool	IsHexDig(int c);
bool	IsUnreserved(int c);
bool	IsSubDelim(int c);
bool	IsPChar(int c);
bool	IsTChar(int c);
bool	IsVChar(int c);
bool	IsSpace(int c);
bool	IsOctet(int c);
bool	IsWhitespace(int c);
bool	IsValidString(int (*validity_checker)(int), std::string const& s,
						std::string const& allow  = std::string());

// mime_types.cpp
std::string	GetType(std::string const& extension);

// status_codes.cpp
bool		IsRedirectCode(int status_code);
std::string GetReasonPhrase(int status_code);

// error classes if stream creation fails
class CreateStreamFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		CreateStreamFailureException(std::string type) {
			_err_string = "ERROR! Failed failed to convert " + type + " to stream.";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~CreateStreamFailureException() throw() {}
};

#endif /* UTILS_HPP */
