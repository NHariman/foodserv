#include <algorithm> // count
#include <cerrno> // erno
#include <dirent.h> // DIR, dirent
#include <sys/types.h> 
#include "file_handler.hpp"
#include "../utils/utils.hpp"
#include "../err/exception.hpp"

#define DEBUG 0 // TODO: REMOVE

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

// Tries to open the file as a stream.
std::istream*	FileHandler::GetFile(std::string const& file_path) {
	if (!IsValidFile(file_path))
		GetFileHandlingError();

	std::istream* file_stream = CreateStreamFromPath(file_path);
	if (file_stream == NULL)
		throw InternalServerErrorException();
	return file_stream;
}

// Returns file extension without '.' or empty string if no extension found.
std::string	FileHandler::GetExtension(std::string const& file_path) const {
	size_t period_pos = file_path.find_last_of('.');

	if (period_pos != std::string::npos)
		return file_path.substr(period_pos + 1);
	return "";
}

void	FileHandler::GetFileHandlingError(void) {
	if (errno == ENOENT)
		throw NotFoundException();
	else if (errno == EACCES)
		throw ForbiddenException();
	else
		throw InternalServerErrorException();
}

std::istream*	FileHandler::ExecuteMethod(Response& response, Method method) {
	switch (method) {
		case Method::Get:
			return ExecuteGet(response);
		case Method::GetError:
			return ExecuteGet(response, true);
		case Method::GetGeneratedIndex:
			return ExecuteGetGeneratedIndex(response);
		case Method::Post:
			return NULL;
		case Method::Delete:
			return NULL;
		default:
			return NULL;
	}
}

// Tries to retrieve file. Sets response status code when done
// if not retrieving error page.
std::istream*	FileHandler::ExecuteGet(Response& response, bool error_page) {
	if (DEBUG) std::cout << "ExecuteGet: path: " << response.GetResolvedPath() << std::endl;

    std::istream*	file = GetFile(response.GetResolvedPath());
	if (!error_page)
		response.SetStatusCode(200);
	return file;
}

// Called when index must be served but index file is not found.
std::istream*	FileHandler::ExecuteGetGeneratedIndex(Response& response) {
	if (DEBUG) std::cout << "ExecuteGetGeneratedIndex: path: " << response.GetResolvedPath() << std::endl;

	std::string	resolved_path = response.GetResolvedPath();

	struct dirent*	dir_entry;
	DIR *dir_path = opendir(resolved_path.c_str());
	if (dir_path == NULL)
		throw InternalServerErrorException();

	std::string index_of = "Index of " + GetTargetDir(response.GetResolvedPath());
	std::string	index = "<html>\r\n<head><title>" + index_of + "</title></head>\r\n"
		+ "<body>\r\n<h1>" + index_of + "</h1><hr>\r\n";

	while ((dir_entry = readdir(dir_path)) != NULL)
		index += FormatLine(dir_entry, resolved_path);
	index += "<hr>\r\n</body>\r\n</html>";
	closedir(dir_path);
	// std::cout<< index << std::endl; // REMOVE
	std::istream* stream = CreateStreamFromString(index);

	response.SetStatusCode(200);
	response.SetHeaderField("Content-Type", "text/html");
	return stream;
}

// Gets directory path without host section.
std::string	FileHandler::GetTargetDir(std::string const& dir_path) {
	if (DEBUG) std::cout << "GetTargetDir\n";

	size_t slash = dir_path.find_first_of("/");
	if (slash == std::string::npos)
		throw InternalServerErrorException();
	
	return dir_path.substr(slash);
}

// Formats readdir returns into html.
std::string	FileHandler::FormatLine(struct dirent* dir_entry, std::string const& path) {
	if (DEBUG) std::cout << "FormatLine\n";
	
	std::string	file_name(dir_entry->d_name);

	// skip prev directory link for security
	if (file_name == ".." || file_name == ".")
		return "";
	// if directory
	else if (dir_entry->d_type == DT_DIR)
		file_name += "/";

	std::string	line = "<a href=\"" + path + file_name + "\">" + file_name + "</a>";
	std::string	last_modified = GetLastModified(path + file_name);

	if (last_modified.empty())
		throw InternalServerErrorException();
	else
		line += " " + last_modified + "\r\n<br>";
	return line;
}

// if POST, validate info and create file. File stream/message should have success/failure message.


#undef DEBUG // REMOVE