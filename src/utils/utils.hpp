#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

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

#endif /* UTILS_HPP */
