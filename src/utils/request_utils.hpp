#ifndef REQUEST_UTILS_HPP
#define REQUEST_UTILS_HPP

#include <algorithm> // transform
#include <iomanip> // setw
#include <ios> // std::hex
#include <iostream>
#include <sstream> // stringstream

bool		PrecededBy(std::string const& read_buf, char c);
void		NormalizeString(int (*convert)(int), std::string& s, size_t start);
std::string	EncodePercent(std::string const& s);
std::string	DecodePercent(std::string const& s);
size_t		MBToBytes(size_t size_mb);
size_t		HextoDec(std::string hex_string);

#include "../err/exception.hpp"

#endif /* REQUEST_UTILS */
