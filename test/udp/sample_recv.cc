#include "udp_stream.h"
#include "udp_epoll_doorman.h"
#include "address.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <utility>

void test() {
    eys::udp_epoll_doorman epoller(200);

    eys::udp_doorman r1(eys::address("0.0.0.0", 1234));
    eys::udp_doorman r2(eys::address("0.0.0.0", 1234));

    epoller.reg(r1, eys::epoll_event_readable);
    epoller.reg(r2, eys::epoll_event_readable);

    int i = 100;
    while(i--) {
        size_t waiting_count = epoller.await();
        if (waiting_count == 0) {
            continue;
        }

        while(waiting_count--) {
            eys::udp_doorman &r = epoller.take();
            int a;
            eys::udp_visitor visitor = r.get_visitor();
            visitor.receive();
            visitor >> a;
            std::cout << visitor.get_fd() << ':' << a << std::endl;
        }
    }
}

int main() {
    test();
    return 0;
}