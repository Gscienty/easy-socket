#include "eys.h"
#include <string>
#include <iostream>
#include <set>
#include <algorithm>

int main() {
    eys::epoll epoller(20);
    eys::tcp_doorman server(eys::address("0.0.0.0", 1800));
    std::set<eys::tcp_visitor, bool (*)(const eys::tcp_visitor &, const eys::tcp_visitor &)> visitors(
        [] (const eys::tcp_visitor &a, const eys::tcp_visitor &b) -> bool {
        return a.get_fd() < b.get_fd();
    });

    epoller.attention(server, eys::epoll_event_readable, [&] (eys::tcp_doorman s, int events) -> void {
        eys::tcp_visitor v = s.get_visitor();
        epoller.attention(v, eys::epoll_event_readable, [] (eys::tcp_visitor c, int events) -> void {
            c.receive();
            std::string seg;
            c >> seg;
            std::cout << seg << std::endl;
            c.send() << "HTTP/1.1 200 OK\r\nContent-Length:13\r\nContent-Type:text/plain\r\n\r\nHello World\r\n";
        });
    });
    int i = 3;
    while (i--) {
        epoller.await();
    }
    return 0;
}