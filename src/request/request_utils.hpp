#ifndef REQUEST_UTILS_HPP
#define REQUEST_UTILS_HPP

#include <cctype> // isalpha, isdigit, toupper
#include <iostream>
#include <string>

using namespace std;

bool	IsHexDig(char c);
bool	IsPChar(char c);
bool	IsTChar(char c);
bool	IsVChar(char c);
bool	IsSpace(char c);
bool	IsValidString(bool (*validity_checker)(char), string const& s); // TODO: Remove if not used
void	NormalizeString(int (*convert)(int), string& s, size_t start);

#endif /* REQUEST_UTILS */
