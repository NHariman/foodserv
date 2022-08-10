#ifndef CHUNKED_PARSER_HPP
#define CHUNKED_PARSER_HPP

#include <string>
#include "state_parser.hpp"

using namespace std;

enum	ChunkState {
	c_Start = 0,
	c_Size,
	c_Data,
	c_Trailer,
	c_Last,
	c_Done,
	c_Invalid
};

class ChunkedParser : public StateParser<ChunkState> {
	static const string	illegal_fields[25];

	public:
		

	private:
};

#endif /* CHUNKED_PARSER_HPP */
