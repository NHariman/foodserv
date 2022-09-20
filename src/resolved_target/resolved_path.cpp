#include "resolved_path.hpp"

#define DEBUG 0

ResolvedPath::ResolvedPath(TargetConfig *target_config, std::string target) : _target_config(target_config), _request_uri(target) {
	_locationblock_uri = _target_config->GetLocationUri().GetUri();
	if (DEBUG) std::cout << "LOCATION BLOCK URI : " << _locationblock_uri << std::endl;
	if (DEBUG) std::cout << "REQUEST URI: " << _request_uri << std::endl;
	_target_config->SetGenerateIndexBool(false);

    if (CheckReturn())
		return ;

	/* checking root and alias goes in an if statement, root will be ignored if alias is set */
	if (_target_config->GetAlias().empty() == false) {
		ReplaceAlias();
	}
	else if (_target_config->GetRoot().empty() == false) {
		AppendRoot();
	}

	if (LocationIsDirectory()) {
		// target_config.SetGenerateIndexBool(false);
		if (_target_config->GetCGIPass().IsSet() == true) {}
		else if (!_target_config->GetAutoindex())
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
	_path = _target_config->GetRoot().append(_request_uri);
}

bool	ResolvedPath::LocationIsDirectory() const {
	if (_path[_path.size() - 1] == '/')
		return true;
	return false;
}

std::string    ResolvedPath::SearchIndexFiles() {
    std::vector<std::string> index_vector = _target_config->GetIndex();

    for (std::vector<std::string>::const_iterator it = index_vector.begin(); it != index_vector.end(); it++) {
		std::string tmp = _path;
		tmp = tmp.append(*it);
		if (IsValidFile(tmp))
			return tmp;
		tmp.clear();
    }
	_target_config->SetGenerateIndexBool(true);
	return _path;
}

void    ResolvedPath::ReplaceAlias() {
	std::string	substr;

	if (DEBUG) std::cout << "in replace alias" << std::endl;
	if (DEBUG) std::cout << "location uri: " << _locationblock_uri << std::endl;
	if (DEBUG) std::cout << "request uri: " << _request_uri << std::endl;
	if (DEBUG) std::cout << "alias: " << _target_config->GetAlias() << std::endl;

	size_t pos = 0;
	while (pos < _locationblock_uri.size() && _locationblock_uri[pos] == _request_uri[pos])
		pos++;
	substr = _request_uri.substr(pos);
	std::string _alias = _target_config->GetAlias();
	_path = _alias.append(substr);
}

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

