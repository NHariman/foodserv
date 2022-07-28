#ifndef REQUEST_UTILS_HPP
#define REQUEST_UTILS_HPP

#include <cctype> // isalpha, isdigit, toupper
#include <iomanip> // setw
#include <iostream>
#include <string>
#include <sstream> // stringstream

using namespace std;

bool	IsHexDig(char c);
bool	IsUnreserved(char c);
bool	IsSubDelim(char c);
bool	IsPChar(char c);
bool	IsTChar(char c);
bool	IsVChar(char c);
bool	IsSpace(char c);
bool	IsWhitespace(char c);
bool	IsValidString(bool (*validity_checker)(char), string const& s); // TODO: Remove if not used
void	NormalizeString(int (*convert)(int), string& s, size_t start);
string	EncodePercent(string const& s);
string	DecodePercent(string const& s);

#endif /* REQUEST_UTILS */
