#include "eys.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

struct string_serializer {
    static std::pair<char *, size_t> serialize(std::string e) {
        char *result = new char[e.size()];
        std::copy(e.begin(), e.end(), result);
        return std::pair<char *, size_t>(result, e.size());
    }

    static std::string deserialize(
            const char *buffer, size_t len, size_t &seek) {
        std::string result(buffer + seek, buffer + seek + len);
        seek += len;
        return result;
    }
};

int main() {
    std::thread udp_sender([] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        eys::udp_sender s(eys::address("127.0.0.1", 1234));

        s.put<std::string, char, string_serializer>("Hello World");

        std::cout << "sender: sent seg \"Hello World\"" << std::endl;
    });

    std::thread udp_receiver([] () -> void {
        eys::udp_doorman d(eys::address("0.0.0.0", 1234));
        eys::udp_visitor v = d.get_visitor();
        v.receive();
        std::string seg;
        v.get<std::string, string_serializer>(seg);

        std::cout << "receiver : " << seg << std::endl; 
    });

    udp_receiver.join();
    udp_sender.join();
    return 0;
}
