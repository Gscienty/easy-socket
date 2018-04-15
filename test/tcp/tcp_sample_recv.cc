#include "tcp_doorman.h"
#include "address.h"
#include <iostream>

int main() {
    eys::tcp_doorman r(eys::address("0.0.0.0", 1234));

    return 0;
}