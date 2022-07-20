#include <iostream>
#include <string>
#include <vector>

class test {
    private:
        std::string _input;
        test(){};
    
    public:
        test(std::string input) { _input = input; };
        ~test(){};
};


int main(void) {
    test *obj;
    std::vector<test> ok;
    return (0);
}