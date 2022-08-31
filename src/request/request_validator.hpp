#ifndef request_validator_HPP
#define request_validator_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request_utils.hpp"

using namespace std;

class Request;
class NginxConfig;

enum HeaderStatus {
	hv_Bad = -1,
	hv_Done = 0,
	hv_MessageExpected,
	hv_MessageChunked
};

class RequestValidator {
	public:
		// Default constructor
		RequestValidator();
		// Destructor
		~RequestValidator();

		HeaderStatus	Process(NginxConfig* config, Request& request);

		bool	ValidHost(string host);
		bool	ValidExpect(Request& request);
		bool	ValidContentEncoding(string host);
		bool	ValidTransferEncoding(Request& request);
		bool	ValidContentLength(NginxConfig* config, Request& request);
		bool	ValidMethod(NginxConfig* config, Request& request);
	
	private:
		HeaderStatus	_status;
};

#endif /* request_validator_HPP */
