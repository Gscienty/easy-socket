#include "tcp_sender.h"
#include "address.h"

int main() {
    eys::tcp_sender s(eys::address("127.0.0.1", 1234));

    s << 2333;
    return 0;
}