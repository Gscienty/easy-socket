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
    std::thread tcp_sender([] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        eys::tcp_sender s(eys::address("127.0.0.1", 1234));

        std::string msg = "Hello World";
        std::cout << msg.size() << std::endl;
        for(int i = 0; i < 10; i++) {
            msg += "Hello World";
        }
        s.put<std::string, char, string_serializer>(msg);

        std::cout << "sender: sent seg \"" << msg << "\"" << std::endl;
    });

    std::thread tcp_receiver([] () -> void {
        eys::tcp_doorman d(eys::address("0.0.0.0", 1234));
        d.watch();
        eys::tcp_visitor v = d.get_visitor(1024);
        
        v.receive();
        std::this_thread::sleep_for(std::chrono::seconds());
        std::string seg;
        v.get<std::string, string_serializer>(seg);
        std::cout << "receiver : " << seg; 

        seg.clear();
        v.get<std::string, string_serializer>(seg);
        std::cout << seg << std::endl;
    });

    tcp_receiver.join();
    tcp_sender.join();
    return 0;
}
