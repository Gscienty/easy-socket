#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

int main() {
    std::thread tcp_sender([] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        eys::tcp_sender s(eys::address("127.0.0.1", 1234));

        s.put(123456789);
    });

    std::thread tcp_receiver([] () -> void {
        eys::tcp_doorman d(eys::address("0.0.0.0", 1234));
        d.watch();
        eys::tcp_visitor v = d.get_visitor(1024);
        
        v.receive();
        int val;
        v.get(val);

        std::cout << val;
    });

    tcp_receiver.join();
    tcp_sender.join();
    return 0;
}
