#include "tcp_doorman.h"
#include "epoll.h"
#include "address.h"
#include <iostream>

int main() {
    eys::tcp_doorman d(eys::address("0.0.0.0", 1234));
    d.watch();

    eys::epoll epoller(200);
    epoller.attention(d, eys::epoll_event_readable, [](eys::base_fd *base, int events) -> void {
        
    });

    return 0;
}
