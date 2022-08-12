#ifndef CHUNKED_PARSER_HPP
#define CHUNKED_PARSER_HPP

#include <string>
#include "header_field_parser.hpp"
#include "state_parser.hpp"
#include "request.hpp"
#include "request_utils.hpp"

using namespace std;

class Request;

enum	ChunkState {
	c_Start = 0,
	c_Size,
	c_Data,
	c_Last,
	c_Trailer,
	c_Done,
	c_Invalid
};

class ChunkedParser : public StateParser<ChunkState> {
	static const vector<string> illegal_fields;

	public:
		// Default constructor
		ChunkedParser();
		// Destructor
		~ChunkedParser();

		size_t Parse(Request& request, string const& input);

	protected:
		ChunkState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;
		bool		CheckDoneState() override;

	private:
		Request*	_request;
		size_t		_chunk_size;
		ChunkState	_save_state;
		bool		_chunk_ext;

		ChunkState	StartHandler(char c);
		ChunkState	SizeHandler(char c);
		ChunkState	DataHandler(char c);
		ChunkState	LastHandler(char c);
		ChunkState	TrailerHandler(char c);
		ChunkState	HandleCRLF(char c, ChunkState return_state, bool skip = true);
		void		ParseTrailerHeader(map<string, string>& fields);
		void		SaveParsedValue();
};

#endif /* CHUNKED_PARSER_HPP */
