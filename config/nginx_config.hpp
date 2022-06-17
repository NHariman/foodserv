/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/06/17 15:59:40 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <map>

class NginxConfig {
	private:
		std::map<std::string, std::string>	config_map;
		NginxConfig(); // cant call default, as file must be added in as argument
		void	loadConfigMap(void);

	public:
		NginxConfig(char *config_file);
		// .. bla bla add in conplien


};

#endif