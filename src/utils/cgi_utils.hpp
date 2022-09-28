#ifndef CGI_UTILS_HPP
#define CGI_UTILS_HPP

#include <string>
#include <iostream>
#include <vector>

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

# define MAX_PATH_LIMIT 1024

bool	IsPath(std::string path);
void	printVector(std::vector<std::string> vec);
std::string GetPWD();
bool        IsAbsolutePath(std::string path);
std::string MakeAbsolutePath(std::string executable, std::string path);



class PWD {
    public:
        PWD();
        ~PWD(){};
        std::string GetCwd() const;
    private:
        std::string _cwd;
};


#endif