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

    epoller.attention(doorman, eys::epoll_event_readable, [] (eys::udp_doorman &d, int events) -> void {
            eys::udp_visitor v = d.get_visitor();
            int val;
            v.receive() >> val;
            std::cout << val << std::endl;
        });

    while (true) epoller.await();
}

int main() {
    test();
    return 0;
}