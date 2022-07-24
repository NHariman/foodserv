#include <iostream>
using namespace std;

int Factorial(int n) {
    if (n < 0)
        cout << "Error! Factorial of a negative number doesn't exist.";
    else {
        long double factorial = 1.0;
        for(int i = 1; i <= n; ++i) {
            factorial *= i;
        }
       return factorial;    
    }
    return 0;
}