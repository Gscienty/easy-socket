#include "udp_stream.h"
#include "address.h"
#include "deserializer.h"
#include <iostream>

int main() {
    char a;
    eys::udp_stream() >> eys::address("0.0.0.0", 1234) >> a;

    std::cout << a << std::endl;
    return 0;
}