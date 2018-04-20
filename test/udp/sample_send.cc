#include "eys.h"
#include <thread>
#include <chrono>

int main() {
    eys::udp_sender out = eys::udp_stream().send(eys::address("127.0.0.1", 1234));

    for (int i = 0; i < 10; i++) {
        out << i;
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}