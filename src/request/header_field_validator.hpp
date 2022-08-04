#ifndef HEADER_FIELD_VALIDATOR_HPP
#define HEADER_FIELD_VALIDATOR_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request.hpp"
#include "request_utils.hpp"

using namespace std;

#ifndef PAYLOAD_LIMIT
#define PAYLOAD_LIMIT 1048576
#endif

class Request;

enum HeaderStatus {
	hv_Bad = -1,
	hv_OK = 0,
	hv_MessageExpected,
	hv_MessageChunked
};

class HeaderFieldValidator {
	public:
		// Default constructor
		HeaderFieldValidator();
		// Destructor
		~HeaderFieldValidator();

		HeaderStatus	Process(Request& request);

		bool	ValidHost(string host);
		bool	ValidExpect(string host);
		bool	ValidContentEncoding(string host);
		bool	ValidContentLength(ssize_t& content_length_count, string host);
		bool	ValidTransferEncoding(ssize_t content_length_count, string host);
	
	private:
		HeaderStatus	_status;
};

#endif /* HEADER_FIELD_VALIDATOR_HPP */
