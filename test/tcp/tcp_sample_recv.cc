#include "tcp_doorman.h"
#include "address.h"
#include <iostream>

int main() {
    eys::tcp_doorman r(eys::address("0.0.0.0", 1234));

    eys::tcp_visitor v = r.get_visitor();
    v.receive();
    int val;
    v >> val;

    std::cout << val << std::endl;

    return 0;
}