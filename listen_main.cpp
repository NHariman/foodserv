#include "src/config/listen.hpp"

int     main() {
    Listen  test1("127.0.0.1:8000");
    Listen  test2("8000");
    Listen  test3("*:8000");
    Listen  test4("localhost:8000");
    Listen  test5("localhost");
    Listen  test6("[::]:8000");
    Listen  test7("[::1]");   
}

