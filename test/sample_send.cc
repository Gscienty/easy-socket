#include "udp_stream.h"
#include "address.h"
#include "serializer.h"
#include <string>

int main() {
    eys::udp_stream().out(eys::address("127.0.0.1", 1234)) << 'A';
    return 0;
}