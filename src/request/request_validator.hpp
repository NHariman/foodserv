#ifndef request_validator_HPP
#define request_validator_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request_utils.hpp"
#include "uri.hpp"

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
		// Config constructor
		RequestValidator(NginxConfig* config);
		// Destructor
		~RequestValidator();

		HeaderStatus	Process(Request& request);

	private:
		HeaderStatus	_status;
		NginxConfig*	_config;
		//TargetConfig*	_target_config;

		bool	PreConfigValidate(Request& request);
		void	SetupConfig(NginxConfig* config, URI const& request_target);
		bool	PostConfigValidate(Request& request);
		bool	ValidHost(Request& request);
		bool	ValidExpect(Request& request);
		bool	ValidContentEncoding(string host);
		bool	ValidTransferEncoding(Request& request);
		bool	ValidContentLength(NginxConfig* config, Request& request);
		bool	ValidMethod(NginxConfig* config, Request& request);
		void	ResolveTarget(Request& request);
};

#endif /* request_validator_HPP */
