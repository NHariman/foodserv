#ifndef HEADER_FIELD_VALIDATOR_HPP
#define HEADER_FIELD_VALIDATOR_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request.hpp"
#include "request_utils.hpp"

using namespace std;

class Request;
class NginxConfig;

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

		HeaderStatus	Process(NginxConfig* config, Request& request);

		bool	ValidHost(string host);
		bool	ValidExpect(string host);
		bool	ValidContentEncoding(string host);
		bool	ValidTransferEncoding(ssize_t content_length_count, string host);
		bool	ValidContentLength(NginxConfig* config, Request& request);
		bool	ValidMethod(NginxConfig* config, Request& request);
	
	private:
		HeaderStatus	_status;
};

#endif /* HEADER_FIELD_VALIDATOR_HPP */
