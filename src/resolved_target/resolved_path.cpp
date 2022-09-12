#include "resolved_path.hpp"

// edge case for only: "/" request

ResolvedPath::ResolvedPath(TargetConfig *target_config) : _target_config(target_config) {
    std::cout << "DIRECTIVE CHECK IN LOCATION: " << std::endl;
    std::cout << "location uri: " << _target_config->GetLocationUri() << std::endl;
    // _path = target_config.GetLocationUri();
    // std::cout << "cgi pass: " << target_config.GetCGIPass() << std::endl;
    // std::cout << "alias: " << target_config.GetAlias() << std::endl;
    std::cout << "root: " << _target_config->GetRoot() << std::endl;
    // std::cout << "index: " << target_config.GetIndex() << std::endl;
    // std::cout << "client max body size: " << target_config.GetClientMaxBodySize() << std::endl;
    // std::cout << "error page: " <<  target_config.GetErrorPage() << std::endl;
    // std::cout << "autoindex: " << target_config.GetAutoindex() << std::endl;
    // std::cout << "return: " << target_config.GetReturn() << std::endl;

    AppendRoot();
}



// if return is found, it immediatly returns this given error
// 

void    ResolvedPath::AppendRoot() {
    // root is always set:
    std::cout << "In append root function with root: " << _target_config->GetRoot() << std::endl;
    std::cout << "And with location uri: " << _target_config->GetLocationUri() << std::endl;

    std::string _path = _target_config->GetRoot();


    _path = _path.append(_target_config->GetLocationUri().GetUri());
    // std::string(_target_config.GetLocationUri());
    std::cout << "PATH: " << _path << std::endl;

}
