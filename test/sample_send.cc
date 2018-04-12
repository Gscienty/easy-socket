#include "udp_stream.h"
#include "address.h"
#include "serializer.h"
#include <string>

int main() {
    int a = 0x12345678;
    eys::udp_stream().out(eys::address("127.0.0.1", 1234)) << a;
    return 0;
}