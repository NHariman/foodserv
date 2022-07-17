#include <vector>
#include <string>
#include <stdexcept>
#include "../../utils.hpp"

class AllowedMethods {
    private:
        std::vector<std::string>    _methods;
		AllowedMethods(){};

		void	ValidateMethods();

    public:
		AllowedMethods(std::string str);
		~AllowedMethods(){};

		std::vector<std::string>	GetAllowedMethods() const;
		void		PrintMethods();
		class BadMethodException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Bad Method in allowed_method detected in LocationBlock.";
				}
		};
};