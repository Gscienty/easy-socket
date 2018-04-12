#include "udp_stream.h"
#include "address.h"
#include <iostream>
#include <string>

int main() {
    int a;
    eys::udp_stream().in(eys::address("0.0.0.0", 1234)) >> a;
    std::cout << std::hex << a << std::endl;
    return 0;
}