#ifndef REQUEST_UTILS_HPP
#define REQUEST_UTILS_HPP

#include <cctype> // isalpha, isdigit, toupper
#include <iostream>

using namespace std;

bool	IsHexDig(char& c);
bool	IsPChar(char c);
bool	IsTChar(char c);
bool	IsVChar(char c);
bool	IsSpace(char c);
bool	IsValidString(bool (*validity_checker)(char), string const& s);

#endif /* REQUEST_UTILS */
