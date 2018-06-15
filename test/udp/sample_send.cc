#include "eys.h"
#include <thread>
#include <chrono>

int main() {
    eys::udp_sender sender(eys::address("0.0.0.0", 1234));

    for (int i = 0; i < 10; i++) {
        sender.put(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
