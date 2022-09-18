#include "resolved_path.hpp"

#define DEBUG 1

// CHECK 1: is return set
// CHECK 2: either append root or alias
// CHECK 3: 

ResolvedPath::ResolvedPath(TargetConfig *target_config, std::string target) : _target_config(target_config), _request_uri(target) {
	_locationblock_uri = _target_config->GetLocationUri().GetUri();
	if (DEBUG) std::cout << "LOCATION BLOCK URI : " << _locationblock_uri << std::endl;
	if (DEBUG) std::cout << "REQUEST URI: " << _request_uri << std::endl;

    if (CheckReturn())
		return ;

	/* checking root and alias goes in an if statement, root will be ignored if alias is set */
	if (_target_config->GetAlias().empty() == false)
		ReplaceAlias();
	else if (_target_config->GetRoot().empty() == false) {
		AppendRoot();
	}

	if (LocationIsDirectory())
		std::cout << "Location is a directory" << std::endl; 

	CleanUpPath();

}

bool	ResolvedPath::CheckReturn() {
    if (_target_config->GetReturn().IsSet()) {
        _path = _target_config->GetReturn().GetUrl();
		return true;
	}
	return false;
}

void    ResolvedPath::AppendRoot() {
	_path = _target_config->GetRoot().append(_locationblock_uri);
}

void	ResolvedPath::RequestIsValidDirectory()  {
    std::cout << "in here" << std::endl;
	if (_target_config->GetAutoindex() == true) {
		std::cout << "AUTO INDEX IS SET" << std::endl;
        // CheckIndexFiles();
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

bool	ResolvedPath::LocationIsDirectory() const {
	if (_locationblock_uri[_locationblock_uri.size() - 1] == '/')
		return true;
	return false;
}

bool    ResolvedPath::SearchIndexFiles() {
    // loop through all index files given
    std::vector<std::string> index_vector = _target_config->GetIndex();
    std::cout << "index vector size: " << index_vector.size();

    for (std::vector<std::string>::const_iterator it = index_vector.begin(); it != index_vector.end(); it++) {
        std::cout << *it << std::endl;
    }
}

void    ResolvedPath::ReplaceAlias() {
	// TO DO
}

// int		ResolvedPath::CharOccurence(std::string str, char c) {
// 	int count = std::count(str.begin(), str.end(), c);
	
// 	std::cout << c << " occurs in \'" << str << "\' " << count << " times." << std::endl;
//  	return count;
// }

void	ResolvedPath::CleanUpPath() {
	std::string	tmp;

	for (int i = 0; i < _path.size(); i++) {
		while (_path[i] == '/' && _path[i + 1] == '/')
			i++;
		tmp += _path[i];
	}
	_path = tmp;
}

std::string	ResolvedPath::GetResolvedPath() const {
	return _path;
}

