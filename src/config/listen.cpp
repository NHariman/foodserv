#include "listen.hpp"

Listen::Listen(std::string listen) : _listen(listen), _port_number(DEFAULT_PORT), _ip_address(DEFAULT_IP) {
	if (_listen.empty()) {
		_port_number = DEFAULT_PORT;
		_ip_address = DEFAULT_IP;
		return ;
	}
	SplitPortIP();
}

void		Listen::SplitPortIP() {
	std::size_t	pos;
	pos = _listen.find_last_of(":");
	if (pos == _listen.size() - 1) {
		if (pos == 0) {
			throw InvalidIpException();
		}
		throw InvalidPortException();
	}
	else if (pos == 0) {
		throw InvalidIpException();
	}
	else if (pos == std::string::npos || (_listen.front() == '[' && _listen.back() == ']')) {
		if (_listen.find('.') != std::string::npos || _listen.find(':') != std::string::npos
			|| _listen.find("localhost") != std::string::npos || _listen.find("*") != std::string::npos
			|| _listen.find('[') != std::string::npos) {
			_port_number = DEFAULT_PORT;
			CheckIpAddress(_listen);
		}
		else {
			_ip_address = DEFAULT_IP;
			CheckPortNumber(_listen);
		}
	}
	else {
		CheckIpAddress(_listen.substr(0, pos));
		CheckPortNumber(_listen.substr(pos + 1, _listen.size()));
	}
}

void		Listen::CheckPortNumber(std::string port_number) {			
	if (port_number.find_first_not_of("0123456789") != std::string::npos)
		throw InvalidPortException();
	else if (stoi(port_number) > 65535 || stoi(port_number) <= 0)
		throw InvalidPortException();
	else if (port_number[0] == '0')
		throw InvalidPortException();
	_port_number = port_number;
}

void		Listen::CheckIpAddress(std::string ip_address) {
	if (ip_address == "localhost")
		_ip_address = "127.0.0.1";
	else if (ip_address == "0" || ip_address == "*")
		_ip_address = DEFAULT_IP;
	else {
		if (CheckValidAddress(ip_address) == false)
			throw InvalidIpException();
		_ip_address = ip_address;
	}
}

bool		Listen::CheckValidAddress(std::string ip_to_check) {
	char	buf[INET6_ADDRSTRLEN];
	int		domain;
	
	if (ip_to_check.find("[") != std::string::npos) {
		domain = AF_INET6;
		ip_to_check = ip_to_check.substr(1, ip_to_check.size() - 2);
	}
	else
		domain = AF_INET;

	if (inet_pton(domain, ip_to_check.c_str(), buf) <= 0) {
		return false;
	}
	return true;
}

std::string		Listen::getPortNumber() {
	return _port_number;
}

std::string		Listen::getIpNumber() {
	return _ip_address;
}
