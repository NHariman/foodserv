/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   LocationBlock.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:39 by nhariman      #+#    #+#                 */
/*   Updated: 2022/06/20 20:52:55 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONBLOCK_HPP
# define LOCATIONBLOCK_HPP

#include <iostream>
#include <map>

class LocationBlock {
	private:
		std::string					uri;
		bool						autoindex;
		std::string					root;
		std::vector<std::string>	*index;
		int							client_max_body_size;
		std::map<int, std::string>	error_page;
};

#endif