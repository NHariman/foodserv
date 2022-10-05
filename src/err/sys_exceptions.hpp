#ifndef SYS_EXCEPTIONS_HPP

# define SYS_EXCEPTIONS_HPP

# include <iostream>
#include <string>
#include <exception>

// exception interface for internal errors like pipe, read etc.
namespace InternalError {
	class exception : public std::exception {
		public:
			virtual const char* what() const throw() = 0;
	};
}

class PipeFailureException : public InternalError::exception
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

class ForkFailureException : public InternalError::exception
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

class WaitFailureException : public InternalError::exception
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

class DupFailureException : public InternalError::exception
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

class MemsetFailureException : public InternalError::exception
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

class ReadFailureException : public InternalError::exception
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

class WriteFailureException : public InternalError::exception
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