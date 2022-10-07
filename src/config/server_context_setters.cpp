#include "server_context.hpp"

void    ServerContext::SetLocation(std::string trimmed_value) {
	_amount_location_context++;
	LocationContext	location(trimmed_value);
	for (size_t i = 0 ; i < _location_contexts.size(); ++i){
		if (_location_contexts[i].GetLocationUri().GetUri().compare(location.GetLocationUri().GetUri()) == 0)
		throw DuplicateLocationUriException(_server_nb, _location_contexts[i].GetLocationUri().GetUri());
	}
	_location_contexts.push_back(location);
}

void    ServerContext::SetListen(std::string trimmed_value) {
    if (bool_listen == true)
		throw MultipleListensException(_server_nb);
	bool_listen = true;
	Listen	listen_port_ip(trimmed_value);
	_listen.first = listen_port_ip.getIpNumber();
	_listen.second = listen_port_ip.getPortNumber();
}

void    ServerContext::SetServerName(std::string trimmed_value) {
	if (bool_server_name == true)
		throw MultipleServerNameException(_server_nb);
	bool_server_name = true;
	ServerName	server_name(trimmed_value);
	_server_name = server_name.GetServerNames();
}

void					ServerContext::CopyValues(const ServerContext& obj) {
	_amount_location_context = obj._amount_location_context;
	bool_listen = obj.bool_listen;
	bool_server_name = obj.bool_server_name;
	bool_root = obj.bool_return_dir;
	bool_index = obj.bool_index;
	bool_client_max_body_size = obj.bool_client_max_body_size;
	bool_error_page = obj.bool_error_page;
	bool_autoindex = obj.bool_autoindex;
	bool_return_dir = obj.bool_return_dir;
	_location_contexts = obj._location_contexts;
	_listen = obj._listen;
	_server_name = obj._server_name;
	_root = obj._root;
	_index = obj._index;
	_client_max_body_size = obj._client_max_body_size;
	_error_page = obj._error_page;
	_autoindex = obj._autoindex;
	_return_dir = obj._return_dir;
	_server_nb = obj._server_nb;
}

void					ServerContext::FindLocationContext(int directive, std::string config_file, size_t *value_end, size_t key_end) {
	*value_end = FindLocationContextEnd(config_file, key_end);
	if (!HasContent('{', key_end, *value_end, config_file) || !HasContent('}', key_end, *value_end, config_file) || !HasContent('\n', key_end, *value_end, config_file))
		throw BadInputException(_server_nb);
	SetValue(directive, config_file.substr(key_end, *value_end - key_end + 1));
}

void					ServerContext::FindValue(int directive, std::string config_file, size_t *value_end, size_t key_end) {
    *value_end = config_file.find_first_of(';', key_end);
	if (!HasContent(';', key_end, *value_end, config_file))
		throw BadInputException(_server_nb);
	SetValue(directive, config_file.substr(key_end, *value_end - key_end));    
}

