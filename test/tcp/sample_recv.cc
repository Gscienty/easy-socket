#include "tcp_doorman.h"
#include "epoll.h"
#include "address.h"
#include <iostream>

int main() {
    eys::tcp_doorman doorman(eys::address("0.0.0.0", 1234));
    doorman.watch();

    eys::epoll epoller(200);
    epoller.attention(doorman, eys::epoll_event_readable, [](eys::tcp_doorman &d, int) -> void {
        eys::tcp_visitor v = d.get_visitor(512);
        v.receive();
        int e;
        v.get(e);
        std::cout << e << std::endl;
    });

    while(true) epoller.await(1);

    return 0;
}
