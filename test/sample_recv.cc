#include "udp_stream.h"
#include "address.h"
#include <iostream>

int main() {
    char a;
    eys::udp_stream().in(eys::address("0.0.0.0", 1234)) >> a;

    std::cout << a << std::endl;
    return 0;
}