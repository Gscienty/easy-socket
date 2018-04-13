#include "tcp_receiver.h"
#include "address.h"
#include <iostream>

int main() {
    eys::tcp_receiver r(eys::address("0.0.0.0", 1234), 1024);
    r.watch();

    eys::tcp_visitor v = r.get_visitor();
    int val;
    v >> val;

    std::cout << val << std::endl;

    return 0;
}