#include "file_handler.hpp"
#include "file_handling.hpp"
#include "exception.hpp"

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

// Tries to open the file as a stream.
std::fstream* FileHandler::GetFile(std::string const& file_path) {
    if (!IsValidFile(file_path))
		throw GetFileHandlingError();

	std::fstream* file_stream = new std::fstream(file_path);
	if (!file_stream.is_open() || !file_stream.good()) {
		throw InternalServerErrorException();
	}
	return file_stream;
}

// Returns file extension without '.' or empty string if no extension found.
std::string FileHandler::GetExtension(std::string const& file_path) const {
    size_t period_pos = file_path.find_last_of('.');

	if (period_pos != string::npos)
		return file_path.substr(period_pos + 1);
	return "";
}

void FileHandler::GetFileHandlingError(void) {
	if (errno == ENOENT)
		throw NotFoundException();
	else if (errno == EACCES)
		throw ForbiddenException();
	else
		throw InternalServerErrorException();
}
