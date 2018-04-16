#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    std::thread udp_sender([] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        eys::udp_sender s(eys::address("127.0.0.1", 1234));

        s << "Hello World";

        std::cout << "sender: sent seg \"Hello World\"" << std::endl;
    });

    std::thread udp_receiver([] () -> void {
        eys::udp_doorman d(eys::address("0.0.0.0", 1234));
        eys::udp_visitor v = d.get_visitor();
        v.receive();
        std::string seg;
        v >> seg;

        std::cout << "receiver : " << seg << std::endl; 
    });

    udp_receiver.join();
    udp_sender.join();
    return 0;
}