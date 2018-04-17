#include "eys.h"
#include <string>
#include <iostream>
#include <set>

int main() {
    eys::epoll epoller(20);
    eys::tcp_doorman d(eys::address("0.0.0.0", 1800));
    std::set<eys::tcp_visitor, bool (*)(const eys::tcp_visitor &, const eys::tcp_visitor &)> visitors(
        [] (const eys::tcp_visitor &a, const eys::tcp_visitor &b) -> bool {
            return a.get_fd() < b.get_fd();
        });

    epoller.attention(d, eys::epoll_event_readable, [&] (eys::tcp_doorman server, int events) -> void {
        eys::tcp_visitor visitor = server.get_visitor();
        visitors.insert(visitor);
        epoller.attention(visitor, eys::epoll_event_readable, [] (eys::tcp_visitor &client, int events) -> void {
            std::cout << client.get_fd() << std::endl;
            std::string seg;
            client.receive();
            client >> seg;
            std::cout << seg << std::endl;
            client.send() << "HTTP/1.1 200 OK\r\nContent-Length:0\r\n\r\n";
        });
    });

    while (true) epoller.await();
    return 0;
}