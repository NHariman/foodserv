#include "location_context.hpp"

LocationContext::LocationContext() {
	_check_list.uri = false;
    _check_list.autoindex = false;
    _check_list.root = false;
    _check_list.index = false;
    _check_list.client_max_body_size = false;
	_check_list.error_page = false;
    _check_list.fastcgi_pass = false;
	_check_list.allowed_methods = false;
}

LocationContext::LocationContext(std::string data) {
    std::cerr << "In LocationContext now" << std::endl;
    _check_list.uri = false;
    _check_list.autoindex = false;
    _check_list.root = false;
    _check_list.index = false;
    _check_list.client_max_body_size = false;
	_check_list.error_page = false;
    _check_list.fastcgi_pass = false;
	_check_list.allowed_methods = false;
    GetDirectiveValuePairs(data);
}

LocationContext& LocationContext::operator= (LocationContext const& location_context) {
    if (this == &location_context)
        return (*this);
    _uri = location_context.GetUri();
    _autoindex = location_context.GetAutoindex();
    _root = location_context.GetRoot();
    _index = location_context.GetIndex();
    _client_max_body_size = location_context.GetClientMaxBodySize();
	_error_page = location_context.GetErrorPage();
    _fastcgi_pass = location_context.GetFastCGIPass();
	_allowed_methods = location_context.GetAllowedMethods();

    _check_list.uri = location_context.GetFlags().uri;
    _check_list.autoindex = location_context.GetFlags().autoindex;
    _check_list.root = location_context.GetFlags().root;
    _check_list.index = location_context.GetFlags().index;
    _check_list.client_max_body_size = location_context.GetFlags().client_max_body_size;
	_check_list.error_page = location_context.GetFlags().error_page;
    _check_list.fastcgi_pass = location_context.GetFlags().fastcgi_pass;
	_check_list.allowed_methods = location_context.GetFlags().allowed_methods;
    return (*this);
}
LocationContext::LocationContext(LocationContext const& location_context) {
    _uri = location_context.GetUri();
    _autoindex = location_context.GetAutoindex();
    _root = location_context.GetRoot();
    _index = location_context.GetIndex();
    _client_max_body_size = location_context.GetClientMaxBodySize();
	_error_page = location_context.GetErrorPage();
    _fastcgi_pass = location_context.GetFastCGIPass();
	_allowed_methods = location_context.GetAllowedMethods();

    _check_list.uri = location_context.GetFlags().uri;
    _check_list.autoindex = location_context.GetFlags().autoindex;
    _check_list.root = location_context.GetFlags().root;
    _check_list.index = location_context.GetFlags().index;
    _check_list.client_max_body_size = location_context.GetFlags().client_max_body_size;
	_check_list.error_page = location_context.GetFlags().error_page;
    _check_list.fastcgi_pass = location_context.GetFlags().fastcgi_pass;
	_check_list.allowed_methods = location_context.GetFlags().allowed_methods;
}

int								LocationContext::IsDirective(std::string directive) {
	const std::string	directives[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "fastcgi_pass", "allowed_methods", "return"};
	
	std::cout << "directive: " << directive << std::endl;
    if (_check_list.uri == false) {
		return 8;
	}
	int	is_directive = std::find(directives, directives + 8, directive) - directives;
	if (is_directive < 0 || is_directive > 7)
		throw InvalidDirectiveException();
	else
		return (is_directive);
}

void							LocationContext::SetValue(int directive, std::string input) {
	std::string		value;

	value = TrimValue(input);
	std::cout << "value: |" << value << "|" << std::endl;

	if (directive == 8) {
		_check_list.uri = true;
		LocationUri		uri_value(value);
		_uri = uri_value;
	}
	else {
		switch(directive) {
			case 0: {
				if (_check_list.autoindex == true)
					throw MultipleAutoindexException();
				_check_list.autoindex = true;
				Autoindex	autoindex_value(value);
				_autoindex = autoindex_value.GetStatus();
				break ;
			}
			case 1: {
				if (_check_list.root == true)
					throw MultipleRootException();
				_check_list.root = true;
				Root root_value(value);
				_root = value;
				break ;
			}
			case 2: {
				if (_check_list.index == true)
					throw MultipleIndexException();
				_check_list.index = true;
				Index	index_value(value);
				_index = index_value.GetIndex();
				break ;
			}
			case 3: {
				if (_check_list.client_max_body_size == true)
					throw MultipleClientMaxBodySizeException();
				_check_list.client_max_body_size = true;
				ClientMaxBodySize	cmbs_value(value);
				_client_max_body_size = cmbs_value.GetValue();
				break ;
			}
            case 4: {
				_check_list.error_page = true;
				ErrorPage	error_page_value(value);
				_error_page.push_back(error_page_value);
				break ;
			}
            case 5: {
				if (_check_list.fastcgi_pass == true)
					throw MultipleFastCGIPassException();
				_check_list.fastcgi_pass = true;
				FastCGIPass fastcgi_pass_value(value);
				_fastcgi_pass = value;
				break ;
			}
            case 6: {
				if (_check_list.allowed_methods == true)
					throw MultipleAllowedMethodsException();
				_check_list.allowed_methods = true;
				AllowedMethods allowed_methods_value(value);
				_allowed_methods = allowed_methods_value;
				break ;
			}
            case 7: {
				if (_check_list.return_dir == true)
					throw MultipleReturnException();
				_check_list.return_dir = true;
				ReturnDir		return_dir_value(value);
				_return_dir = return_dir_value;
				break ;
			}
		}
	}
}

void							LocationContext::CheckListVerification(){
    if (_check_list.autoindex == false) {
		_autoindex = false;
		std::cerr << "WARNING! No autoindex in LocationContext detected. Default (off) have been set." << std::endl;
	}
    if (_check_list.root == false) {
		_root = "/var/www/html";
		std::cerr << "WARNING! No location root detected. Default (/var/www/html) have been set." << std::endl;
	}
	if (_check_list.index == false) {
		Index	input_value("index.php index.html index.htm index.nginx-debian.html");
		_index = input_value.GetIndex();
		std::cerr << "WARNING! No location index detected. Default (index.php index.html index.htm index.nginx-debian.html) have been set." << std::endl;
	}
	if (_check_list.client_max_body_size == false) {
		_client_max_body_size = 0;
		std::cerr << "WARNING! No client_max_body_size in LocationContext detected. Default (0) have been set." << std::endl;
	}
	if (_check_list.allowed_methods == false)
		std::cerr << "WARNING! No allowed_methods in LocationContext detected. Default (No methods allowed) have been set." << std::endl;
}

void							LocationContext::GetDirectiveValuePairs(std::string data) {
    size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					ret;
    int                 i = 0;
    
    while (data[i] != '}') {
		key_start = data.find_first_not_of(" \t\n\v\f\r", i);
		if (data[key_start] == '}') {
			break ;
		}
		key_end = data.find_first_of(" \t\n\v\f\r", key_start);
		ret = IsDirective(data.substr(key_start, key_end - key_start));
		if (ret == 7) {
			std::cout << "uri block found" << std::endl;
            SetValue(ret, data.substr(key_start, key_end - key_start));
			value_end = data.find_first_of('{', key_end);
		}
		else {
            value_end = data.find_first_of(';', key_end);
		    SetValue(ret, data.substr(key_end, value_end - key_end));
        }
		i = value_end + 1;
	}
	CheckListVerification();
}

// getters
LocationUri							LocationContext::GetUri() const {
    return _uri;
}

bool								LocationContext::GetAutoindex() const {
    return _autoindex;
}

std::string							LocationContext::GetRoot() const {
    return _root;
}

std::vector<std::string>			LocationContext::GetIndex() const {
    return _index;
}

int									LocationContext::GetClientMaxBodySize() const {
    return _client_max_body_size;
}

std::vector<ErrorPage>				LocationContext::GetErrorPage() const {
    return _error_page;
}

std::string							LocationContext::GetFastCGIPass() const {
    return _fastcgi_pass;
}

AllowedMethods						LocationContext::GetAllowedMethods() const {
    return _allowed_methods;
}

t_flags_location					LocationContext::GetFlags() const {
	return _check_list;
}

// use to check if a directive has been set
bool						LocationContext::IsSet(std::string directive) {
	const std::string	directives[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "fastcgi_pass", "allowed_methods", "return"};

	int	is_directive = std::find(directives, directives + 8, directive) - directives;
	if (is_directive < 0 || is_directive > 7)
		throw InvalidDirectiveSetCheckException();
	switch (is_directive) {
		case 0:
			return _check_list.autoindex;
		case 1:
			return _check_list.root;
		case 2:
			return _check_list.index;
		case 3:
			return _check_list.client_max_body_size;
		case 4:
			return _check_list.error_page;
		case 5:
			return _check_list.fastcgi_pass;
		case 6:
			return _check_list.allowed_methods;
		case 7:
			return _check_list.return_dir;
	}
	throw InvalidDirectiveException();
}