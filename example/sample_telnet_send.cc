#include "eys.h"
#include <iostream>

int main() {
    eys::tcp_sender sender(eys::address("127.0.0.1", 1234));

    for (int i = 0; i < 10; i++) {
        char c;
        std::cin >> c;
        sender << c;
    }

    return 0;
}