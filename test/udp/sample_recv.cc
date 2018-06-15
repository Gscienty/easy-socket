#include "eys.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <utility>

void test() {
    eys::udp_doorman doorman(eys::address("0.0.0.0", 1234));
    eys::epoll epoller(200);

    epoller.attention(
            doorman, eys::epoll_event_readable, [] (eys::udp_doorman &d, int) -> void {
            eys::udp_visitor v = d.get_visitor();
            v.receive();
            int e;
            v.get(e);
            std::cout << e << std::endl;
        });

    while (true) epoller.await();
}

int main() {
    test();
    return 0;
}
