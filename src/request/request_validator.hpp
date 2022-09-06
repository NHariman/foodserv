#ifndef REQUEST_VALIDATOR_HPP
#define REQUEST_VALIDATOR_HPP

#include <map>
#include <string>
#include "exception.hpp"
#include "request_utils.hpp"
#include "uri.hpp"

using namespace std;

class Request;
class NginxConfig;
class TargetConfig;

enum HeaderStatus {
	hv_Bad = -1,
	hv_Done = 0,
	hv_MessageExpected,
	hv_MessageChunked
};

class RequestValidator {
	public:
		// Config constructor
		RequestValidator(NginxConfig* config, TargetConfig* target_config);
		// Destructor
		~RequestValidator();

		HeaderStatus	Process(Request& request);

	private:
		HeaderStatus	_status;
		NginxConfig*	_config;
		TargetConfig*	_target_config;

		bool	PreConfigValidate(Request& request);
		int		SetupConfig(NginxConfig* config, Request const& request);
		bool	PostConfigValidate(Request& request);
		bool	ValidHost(Request& request);
		bool	ValidExpect(Request& request);
		bool	ValidContentEncoding(string const& host);
		bool	ValidTransferEncoding(Request& request);
		bool	ValidContentLength(Request& request);
		bool	ValidMethod(string const& method);
		void	ResolveTarget(Request& request);
};

#endif /* REQUEST_VALIDATOR_HPP */