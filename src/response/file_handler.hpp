#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <cerrno>
#include <fcntl.h> // open

class FileHandler {
	public:
		FileHandler();
		~FileHandler();

		std::fstream*	GetFile(std::string const& file_path);
		std::string		GetExtension(std::string const& file_path) const;
	
	private:
		void	GetFileHandlingError(void);
};

#endif /* FILE_HANDLER_HPP */
