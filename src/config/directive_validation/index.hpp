#ifndef INDEX_HPP
# define INDEX_HPP

#include <vector>
#include <string>
#include "../../utils/config_utils.hpp"

class Index {
    private:
        std::vector<std::string> _index;
		Index(){};
    
    public:
		Index(std::string value);
		~Index(){};

		std::vector<std::string>	GetIndex() const;
		void						PrintIndex();
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in index block.";
				}
		};
};

#endif