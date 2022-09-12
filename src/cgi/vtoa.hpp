#ifndef VTOA_HPP
# define VTOA_HPP

# include <vector>
#include <string>

class vtoa {
	private:
		char *const * _array;
		vtoa();
	public:
		vtoa(std::vector<std::string> vec);
		~vtoa();
		char *const * GetArray() const;
};

#endif

