#ifndef KERNEL_EVENTS_HPP
# define KERNEL_EVENTS_HPP

#include <vector>
#include <iostream>
// #include <sys/types.h>
#include <sys/event.h>
// #include <sys/time.h>

class KernelEvents {
	private:
		std::vector<int>	_listening_sockets;
		int					_kqueue;
	
		void	KqueueInit();
	
	public:
		KernelEvents(std::vector<int> listening_sockets);


	class KqueueCreationException : public std::exception {
	public:
		const char *what() const throw() {
			return "ERROR! Failed to create kqueue.";
		}
	};
};

#endif
