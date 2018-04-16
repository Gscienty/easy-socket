#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    eys::tcp_doorman d(eys::address("0.0.0.0", 1801));
    std::cout << d.watch() << std::endl;
    std::cout << "waiting..." << std::endl;
    while (true) {
        eys::tcp_visitor v = d.get_visitor();
        std::cout << "welcome" << std::endl;
        v.receive();
        // std::string seg;
        // v >> seg;
        v.send() << "HTTP/1.1 200 OK\r\nContent-Type:text/plain\r\nContent-Length:11\r\n\r\nHello World";
    
    }
    return 0;
}