#ifndef HEADER_FIELD_VALIDATOR_HPP
#define HEADER_FIELD_VALIDATOR_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request.hpp"

using namespace std;

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

		HeaderStatus	Process(Request const& request);
		bool 			ValidHost(string host);
		bool 			ValidTransferEncoding(string host);
		bool 			ValidContentEncoding(string host);
		bool 			ValidContentLength(string host);
		bool 			ValidExpect(string host);
	
	private:
		HeaderStatus	_status;
};

#endif /* HEADER_FIELD_VALIDATOR_HPP */
