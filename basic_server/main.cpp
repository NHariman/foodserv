#include "server.hpp"
#include <sys/socket.h>

int     main() {
    Server servie(80, INADDR_ANY);
}