#include "udp_stream.h"
#include "udp_epoll_receiver.h"
#include "address.h"
#include <iostream>
#include <string>

int main() {

    eys::udp_epoll_receiver epoller(200);

    eys::udp_single_receiver r1(eys::address("0.0.0.0", 1234), 1024);
    eys::udp_single_receiver r2(eys::address("0.0.0.0", 1234), 1024);

    epoller.reg(r1, eys::epoll_event_readable);
    epoller.reg(r2, eys::epoll_event_readable);

    return 0;
}