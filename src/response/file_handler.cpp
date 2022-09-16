#include "file_handler.hpp"
#include "exception.hpp"
#include "file_handling.hpp"

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

std::string FileHandler::GetFileContents(std::string const& file_path) {
    if (!IsValidFile(file_path))
		throw ForbiddenException();
	int fd = open(file_path.c_str(), O_RDONLY);
	if (fd < 0)
		throw ForbiddenException();

	std::string file_content;
	// read into buffer & add to file_content
	close(fd);
	return file_content;
}

// Returns file extension without '.' or empty string if no extension found.
std::string FileHandler::GetExtension(std::string const& file_path) const {
    size_t period_pos = file_path.find_last_of('.');

	if (period_pos != string::npos)
		return file_path.substr(period_pos + 1);
	return "";
}
