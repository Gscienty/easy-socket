#include "udp_stream.h"
#include "epoll.h"
#include "address.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <utility>

void test() {
    eys::epoll epoller(200);

    eys::udp_doorman doorman(eys::address("0.0.0.0", 1234));

    std::function<void(eys::udp_doorman &, int)> func = [] (eys::udp_doorman &d, int events) -> void {
        eys::udp_visitor v = d.get_visitor();
        int val;
        v.receive() >> val;
        std::cout << val << std::endl;
    };
    epoller.attention(doorman, eys::epoll_event_readable, func);

    while (true) epoller.await();
}

int main() {
    test();
    return 0;
}