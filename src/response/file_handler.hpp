#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <fstream> // ifstream
#include <cerrno> // erno

class FileHandler {
	public:
		FileHandler();
		~FileHandler();

		std::ifstream*	GetFile(std::string const& file_path);
		std::string		GetExtension(std::string const& file_path) const;
	
	private:
		void	GetFileHandlingError(void);
};

#endif /* FILE_HANDLER_HPP */
