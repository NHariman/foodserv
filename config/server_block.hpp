/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:35:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/05 20:01:51 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BLOCK_HPP
# define SERVER_BLOCK_HPP
#include <iostream>
#include <map>
#include "location_block.hpp"
#include <vector>
#include <string>

class ServerBlock {
	private:
		struct s_components
		{
			int		location_block;
			bool	listen;
			bool	server_name;
			bool	root;
			bool	index;
			bool	client_max_body_size;
			bool	error_page;
		}	_check_list; // check list of found keywords in serverblock

		std::vector<LocationBlock>	_location_blocks;
		std::string					_listen; // parse in here -> or make listen a class
		std::string					_server_name; // make it a class
		std::string					_root;
		std::string					_index;
		int							_client_max_body_size; // inherits from NginxConfig if undefined
		std::map<int, std::string>	_error_page; // inherits from NginxConfig if undefined

		
	public:
		ServerBlock(std::ifstream &file, size_t *start); // uses a pointer so it can skip through the server bits on its own when it returns
		ServerBlock();
		ServerBlock(const ServerBlock &server_block);
		ServerBlock & operator= (const ServerBlock &server_block);
		~ServerBlock(){};
		
		size_t		FindKeyValuePairs(size_t *start_position, std::string config_file);
		std::vector<LocationBlock>	GetLocationBlocks() const;
		std::string					GetListen() const; // parse in here -> or make listen a class
		std::string					GetServerName() const; // make it a class
		std::string					GetRoot() const;
		std::string					GetIndex() const;
		int							GetClientMaxBodySize() const; // inherits from NginxConfig if undefined
		std::map<int, std::string>	GetErrorPage() const; // inherits from NginxConfig if undefined		

};

#endif