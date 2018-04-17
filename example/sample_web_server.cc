#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

int main() {
    eys::tcp_doorman d(eys::address("0.0.0.0", 1802));
    std::cout << "waiting..." << std::endl;
    int i = 5;
    std::vector<eys::tcp_visitor> fuck;
    while (i--) {
        fuck.push_back(d.get_visitor());
        std::cout << "welcome" << std::endl;
        size_t s = (*(fuck.rbegin())).receive();
        if (s == 0) {
            continue;
        }
        std::string seg;
        *(fuck.rbegin()) >> seg;
        (*(fuck.rbegin())).send() << "HTTP/1.1 200 OK\r\nContent-Type:text/plain\r\nContent-Length:13\r\n\r\nHello World\r\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}