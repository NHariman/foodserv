#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

#define MAX_CHUNKEXT_SIZE 8192 // used by ChunkedParser
#define MAX_HEADER_SIZE	8192 // used by HeaderFieldParser
#define MAX_URI_SIZE 8192 // used by RequestTargetParser
#define BUFFER_SIZE 4096

// file_handling.cpp
bool	IsValidFile(std::string const& path);
bool	IsValidDirectory(std::string const& path);

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
std::string GetReasonPhrase(int status_code);

#endif /* UTILS_HPP */
