#include "resolved_path.hpp"

// edge case for only: "/" request

ResolvedPath::ResolvedPath(TargetConfig target_config) {
    std::cout << "DIRECTIVE CHECK IN LOCATION: " << std::endl;
    std::cout << "location uri: " << target_config.GetLocationUri() << std::endl;
    // _path = target_config.GetLocationUri();
    // std::cout << "cgi pass: " << target_config.GetCGIPass() << std::endl;
    // std::cout << "alias: " << target_config.GetAlias() << std::endl;
    std::cout << "root: " << target_config.GetRoot() << std::endl;
    // std::cout << "index: " << target_config.GetIndex() << std::endl;
    // std::cout << "client max body size: " << target_config.GetClientMaxBodySize() << std::endl;
    // std::cout << "error page: " <<  target_config.GetErrorPage() << std::endl;
    // std::cout << "autoindex: " << target_config.GetAutoindex() << std::endl;
    // std::cout << "return: " << target_config.GetReturn() << std::endl;
}



// if return is found, it immediatly returns this given error
// 

void    ResolvedPath::AppendRoot() {
    //
}