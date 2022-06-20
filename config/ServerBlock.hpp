/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerBlock.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:35:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/06/20 20:50:18 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERBLOCK_HPP
# define SERVERBLOCK_HPP
#include <iostream>
#include <map>
#include "LocationBlock.hpp"

class ServerBlock {
	private:
		std::vector<LocationBlock>	*location_blocks;
		int							listen;
		std::vector<std::string>	*server_name;
		std::string					root;
		std::vector<std::string>	*index;
		int							client_max_body_size;
		std::map<int, std::string>	error_page;
};

#endif