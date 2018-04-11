#include "udp_stream.h"
#include "address.h"
#include "serializer.h"
#include <string>

int main() {
    eys::udp_stream() << eys::address("0.0.0.0", 1234) << 'A';
    return 0;
}