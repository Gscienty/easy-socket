#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    std::thread tcp_sender([] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        eys::tcp_sender s(eys::address("127.0.0.1", 1234));

        std::string msg = "Hello World";
        s << msg;

        std::cout << "sender: sent seg \"Hello World\"" << std::endl;
    });

    std::thread tcp_receiver([] () -> void {
        eys::tcp_doorman d(eys::address("0.0.0.0", 1234));
        d.watch();
        eys::tcp_visitor v = d.get_visitor(65536);
        
        v.receive();
        std::string seg;
        v >> seg;

        std::cout << "receiver : " << seg.length() << std::endl; 
    });

    tcp_receiver.join();
    tcp_sender.join();
    return 0;
}