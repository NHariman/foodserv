#ifndef CHUNKED_PARSER_HPP
#define CHUNKED_PARSER_HPP

#include <string>
#include <vector>
#include "astate_parser.hpp"
#include "../utils/request_utils.hpp"
#include "../utils/utils.hpp"

class Request;

enum	ChunkState {
	c_Start = 0,
	c_Size,
	c_Data,
	c_Last,
	c_Trailer,
	c_End,
	c_Done,
	c_Invalid
};

class ChunkedParser : public AStateParser<ChunkState> {
	static const std::vector<std::string> illegal_fields;

	public:
		// Default constructor
		ChunkedParser();
		// Destructor
		~ChunkedParser();

		size_t Parse(Request& request, std::string const& input);

	protected:
		ChunkState	GetNextState(size_t pos) override;
		void		CheckInvalidState() const override;
		void		AfterParseCheck() override;

	private:
		Request*	_request;
		size_t		_chunk_size;
		size_t		_chunk_ext_size;
		bool		_chunk_ext;
		bool		_chunk_trailer;
		bool		_cr; // keeps track of when CR is found
		
		ChunkState	StartHandler(char c);
		ChunkState	SizeHandler(char c);
		ChunkState	DataHandler(char c);
		ChunkState	LastHandler(char c);
		ChunkState	TrailerHandler(char c);
		ChunkState	EndHandler(char c);
		ChunkState	HandleChunkExtension(char c);
		ChunkState	HandleCRLF(char c, ChunkState return_state, bool skip = true);
		void		ParseTrailerHeader();
		void		SaveParsedValue();
};

#endif /* CHUNKED_PARSER_HPP */
