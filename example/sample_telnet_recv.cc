#include "eys.h"
#include <iostream>

int main() {
    eys::epoll epoller(20);

    epoller.attention(
        eys::tcp_doorman(eys::address("0.0.0.0", 1234)),
        eys::epoll_event_readable,
        [&] (eys::tcp_doorman &server, int events) -> void {
            epoller.attention(
                server.get_visitor(),
                eys::epoll_event_readable,
                [] (eys::tcp_visitor &client, int events) -> void {
                    client.receive();
                    char c;
                    client >> c;
                    std::cout << c;
                }
            );
        }
    );

    while (50) epoller.await();
    return 0;
}