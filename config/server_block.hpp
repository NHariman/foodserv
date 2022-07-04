/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:35:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/04 14:30:28 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BLOCK_HPP
# define SERVER_BLOCK_HPP
#include <iostream>
#include <map>
#include "location_block.hpp"

class ServerBlock {
	protected:
		std::vector<LocationBlock>	location_blocks;
		std::string					listen; // parse in here -> or make listen a class
		std::string					server_name; // make it a class
		std::string					root;
		std::string					index;
		int							client_max_body_size; // inherits from NginxConfig if undefined
		std::map<int, std::string>	error_page; // inherits from NginxConfig if undefined
		ServerBlock(){};
	public:
		ServerBlock(std::ifstream &file, size_t *start); // uses a pointer so it can skip through the server bits on its own when it returns
		~ServerBlock(){};
};

#endif