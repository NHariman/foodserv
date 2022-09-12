#include "resolved_path.hpp"

// edge case for only: "/" request

ResolvedPath::ResolvedPath(TargetConfig *target_config, std::string target) : _target_config(target_config), _request_uri(target) {
    std::cout << "DIRECTIVE CHECK IN LOCATION: " << std::endl;
    // _path = target_config.GetLocationUri();
    // std::cout << "cgi pass: " << target_config.GetCGIPass() << std::endl;
    // std::cout << "alias: " << target_config.GetAlias() << std::endl;
    // std::cout << "root: " << _target_config->GetRoot() << std::endl;
    // std::cout << "index: " << target_config.GetIndex() << std::endl;
    // std::cout << "client max body size: " << target_config.GetClientMaxBodySize() << std::endl;
    // std::cout << "error page: " <<  target_config.GetErrorPage() << std::endl;
    // std::cout << "autoindex: " << target_config.GetAutoindex() << std::endl;
    // std::cout << "return: " << target_config.GetReturn() << std::endl;

	_locationblock_uri = _target_config->GetLocationUri().GetUri();
	std::cout << "LOCATION BLOCK URI : " << _locationblock_uri << std::endl;
	std::cout << "REQUEST URI: " << _request_uri << std::endl;

    if (target_config->GetAlias().empty() == false) // misschien naar isSet
        SetAlias();
    else
        AppendRoot();
}


// RETURN DIRECTIVE

void    ResolvedPath::AppendRoot() {
    std::string _path = _target_config->GetRoot();


    _path = _path.append(_request_uri);
    // std::string(_target_config.GetLocationUri());
    std::cout << "PATH: " << _path << std::endl;

}

void    ResolvedPath::SetAlias() {
    std::cout << "In set alias function with alias: " << _target_config->GetAlias() << std::endl;
    std::cout << "and location uri: " << _locationblock_uri << std::endl;
    std::cout << "request uri: " << _request_uri<< std::endl;


	CharOccurence(_locationblock_uri, '/');
	CharOccurence(_request_uri, '/');
}

int		ResolvedPath::CharOccurence(std::string str, char c) {
	int count = std::count(str.begin(), str.end(), c);
	
	std::cout << c << " occurs in \'" << str << "\' " << count << " times." << std::endl;
 	return count;
	// std::cout << c 
	// std::cout << 
}
//     #include <iostream>
// #include <algorithm>
// #include <string>
 
// int main()
// {
//     std::string s = "C++,Java";
//     char ch = '+';
 
//     int count = std::count_if (s.begin(), s.end(),
//                             [&ch](char c) {
//                                 return c == ch;
//                             });
//     std::cout << "Character " << ch << " occurs " << count << " times";
 
//     return 0;
// }
// }
