#include "resolved_path.hpp"

#define DEBUG 0

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

	if (LocationIsDirectory()) {
		if (!_target_config->GetAutoindex())
			_path = "";
		else
			_path = SearchIndexFiles();
	}

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

bool	ResolvedPath::LocationIsDirectory() const {
	if (_locationblock_uri[_locationblock_uri.size() - 1] == '/')
		return true;
	return false;
}

std::string    ResolvedPath::SearchIndexFiles() {
    std::vector<std::string> index_vector = _target_config->GetIndex();

    for (std::vector<std::string>::const_iterator it = index_vector.begin(); it != index_vector.end(); it++) {
		std::string tmp = _path;
		tmp = tmp.append(*it);
		if (IsValidFile(tmp)) {
			return tmp;
		}
		tmp.clear();
    }
	return "";
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

	for (size_t i = 0; i < _path.size(); i++) {
		while (_path[i] == '/' && _path[i + 1] == '/')
			i++;
		tmp += _path[i];
	}
	_path = tmp;
}

std::string	ResolvedPath::GetResolvedPath() const {
	return _path;
}

