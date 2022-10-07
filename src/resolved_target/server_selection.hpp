#ifndef SERVER_SELECTION_HPP
# define SERVER_SELECTION_HPP

#include "../config/server_context.hpp"

class ServerSelection {
	private:
		ServerSelection();
		
		std::string					_port;
		std::string					_host;
		std::vector<ServerContext>	_serverblocks;
		std::vector<ServerContext>	_compatible_serverblocks;
		ServerContext				_chosen_servercontext;
		
		bool			SelectCompatiblePorts(std::string ports);
		void			SelectCompatibleServerNames(std::string, std::vector<ServerContext>);

	public:
		ServerSelection(std::string host, std::string port, std::vector<ServerContext>);
		ServerContext	GetChosenServerContext() const;
		std::string		GetHost();
		void			PrintChosenServerblock();
		void			PrintContextVectors();
};

#endif
