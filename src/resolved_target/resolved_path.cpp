#include "resolved_path.hpp"

// edge case for only: "/" request

ResolvedPath::ResolvedPath(TargetConfig *target_config, std::string target) : _target_config(target_config), _request_uri(target) {
    std::cout << "DIRECTIVE CHECK IN LOCATION: " << std::endl;
    // _path = target_config.GetLocationUri();
    // std::cout << "cgi pass: " << target_config.GetCGIPass() << std::endl;
    // std::cout << "alias: " << target_config.GetAlias() << std::endl;
    // std::cout << "root: " << _target_config->GetRoot() << std::endl;
    // std::cout << "index: " << target_config.GetIndex() << std::endl;
    // std::cout << "error page: " <<  target_config.GetErrorPage() << std::endl;
    // std::cout << "autoindex: " << target_config.GetAutoindex() << std::endl;
    // std::cout << "return: " << target_config.GetReturn() << std::endl;

	_locationblock_uri = _target_config->GetLocationUri().GetUri();
	std::cout << "LOCATION BLOCK URI : " << _locationblock_uri << std::endl;
	std::cout << "REQUEST URI: " << _request_uri << std::endl;

    // replace this for if directory function
    if (_request_uri[_request_uri.size() - 1] != '/') {
        if (target_config->GetReturn().IsSet() == true) {
            std::cout << "return is set: " << target_config->GetReturn().GetUrl() << std::endl;
            _path = target_config->GetReturn().GetUrl();
        }
        else if (target_config->GetAlias().empty() == false) // misschien naar isSet
            ReplaceAlias();
        else
            AppendRoot();
    }
    // else {
    //     if autoinex is set
    // }
}


// RETURN DIRECTIVE
void    ResolvedPath::ReplaceReturn() {
    // if this happends, i also need to send a return code 301
    _path = _target_config->GetReturn().GetUrl();
    std::cout << "final path" << std::endl;
}

void    ResolvedPath::AppendRoot() {
    std::string _path = _target_config->GetRoot();


    _path = _path.append(_request_uri);
    // std::string(_target_config.GetLocationUri());
    std::cout << "PATH: " << _path << std::endl;

}

void    ResolvedPath::ReplaceAlias() {
    std::cout << "In set alias function with alias: " << _target_config->GetAlias() << std::endl;
    std::cout << "and location uri: " << _locationblock_uri << std::endl;
    std::cout << "request uri: " << _request_uri<< std::endl;


	// CharOccurence(_locationblock_uri, '/');
	// CharOccurence(_request_uri, '/');
}

int		ResolvedPath::CharOccurence(std::string str, char c) {
	int count = std::count(str.begin(), str.end(), c);
	
	std::cout << c << " occurs in \'" << str << "\' " << count << " times." << std::endl;
 	return count;
}

std::string	ResolvedPath::GetResolvedPath() const {
	return _path;
}

