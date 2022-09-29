#ifndef C_EXCEPTIONS_HPP

# define C_EXCEPTIONS_HPP

# include <iostream>
#include <string>
#include <exception>

class PipeFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		PipeFailureException() {
			_err_string = "ERROR! Failed to create pipe.";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~PipeFailureException() throw() {}
};

class ForkFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		ForkFailureException() {
			_err_string = "ERROR! Failed to create fork.";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~ForkFailureException() throw() {}
};

class WaitFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		WaitFailureException() {
			_err_string = "ERROR! Failed waitpid.";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~WaitFailureException() throw() {}
};

class DupFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		DupFailureException() {
			_err_string = "ERROR! Failed dup2.";
		}
		DupFailureException(std::string fd) {
			_err_string = "ERROR! Failed dup2 at fd: " + fd;
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~DupFailureException() throw() {}
};

class MemsetFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		MemsetFailureException() {
			_err_string = "ERROR! Failed memset().";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~MemsetFailureException() throw() {}
};

class ReadFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		ReadFailureException() {
			_err_string = "ERROR! Failed read().";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~ReadFailureException() throw() {}
};

class WriteFailureException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		WriteFailureException() {
			_err_string = "ERROR! Failed write().";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~WriteFailureException() throw() {}
};

#endif