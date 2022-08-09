#ifndef REQUEST_UTILS_HPP
#define REQUEST_UTILS_HPP

#include <cctype> // isalpha, isdigit, toupper
#include <iomanip> // setw
#include <iostream>
#include <string>
#include <sstream> // stringstream

using namespace std;

bool	IsHexDig(int c);
bool	IsUnreserved(int c);
bool	IsSubDelim(int c);
bool	IsPChar(int c);
bool	IsTChar(int c);
bool	IsVChar(int c);
bool	IsSpace(int c);
bool	IsWhitespace(int c);
bool	IsValidString(int (*validity_checker)(int), string const& s,
						string const& allow  = std::string());
bool	PrecededBy(string const& read_buf, char c);
void	NormalizeString(int (*convert)(int), string& s, size_t start);
string	EncodePercent(string const& s);
string	DecodePercent(string const& s);
size_t	MBToBytes(size_t size_mb);

#endif /* REQUEST_UTILS */
