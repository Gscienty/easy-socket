#include "tcp_sender.h"
#include "address.h"
#include <thread>
#include <chrono>


int main() {
    eys::tcp_sender s(eys::address("127.0.0.1", 1234));

    for (int i = 1; i < 10; i++) {
       std::this_thread::sleep_for(std::chrono::seconds(1));
       s.put(i);
    }

    return 0;
}
