#include "resolved_path.hpp"

#define DEBUG 1

// CHECK 1: is return set
// CHECK 2: either append root or alias
// CHECK 3: 

ResolvedPath::ResolvedPath(TargetConfig *target_config, std::string target) : _target_config(target_config), _request_uri(target) {
	_locationblock_uri = _target_config->GetLocationUri().GetUri();
	if (DEBUG) std::cout << "LOCATION BLOCK URI : " << _locationblock_uri << std::endl;
	if (DEBUG) std::cout << "REQUEST URI: " << _request_uri << std::endl;

    /* If return is set, we set the path to what return gives are url for redirection */
    if (target_config->GetReturn().IsSet()) {
        _path = _target_config->GetReturn().GetUrl();
    }
    /* Check is the request if a directory */
    else if (_request_uri[_request_uri.size() - 1] == '/') { // change this for utils: isDirectory function
        if (IsValidDirectory(_request_uri)) {
            std::cout << "the request uri is a existing direcotry" << std::endl;
			RequestIsValidDirectory();
        }
        else {
            std::cout << "it is not exsisting" << std::endl;
			// return an empty string.
			_path = "";
        }
    }
	else {
		std::cout << "request is not a directory" << std::endl;
		if (target_config->GetAlias().empty() == false)
			ReplaceAlias();
		else
			AppendRoot();
	}

    // if (_request_uri[_request_uri.size() - 1] != '/') {
    //     else if (target_config->GetAlias().empty() == false) // misschien naar isSet
    //         ReplaceAlias();
    //     else
    //         AppendRoot();
    // }
    // // else {
    // //     if autoinex is set
    // // }
}

void	ResolvedPath::RequestIsValidDirectory()  {
    std::cout << "in here" << std::endl;
	if (_target_config->GetAutoindex() == true) {
		std::cout << "AUTO INDEX IS SET" << std::endl;
        CheckIndexFiles();
        // if (CheckIndex()) {
            // return file _path = file path
        // }
        // else {
            // _path = directory path
        // }
        // now go through all index files, to see if one of them exists
        // if one exists -> send this path
        // if none exist -> send the path up to directory
    }

}

bool    ResolvedPath::CheckIndexFiles() {
    // loop through all index files given
    std::vector<std::string> index_vector = _target_config->GetIndex();
    std::cout << "index vector size: " << index_vector.size();

    for (std::vector<std::string>::const_iterator it = index_vector.begin(); it != index_vector.end(); it++) {
        std::cout << *it << std::endl;
    }
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
	// replace alias still needs a lot of work

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

