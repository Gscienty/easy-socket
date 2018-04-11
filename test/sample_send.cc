#include "udp_stream.h"
#include "address.h"
#include "serializer.h"

int main() {
    eys::udp_sender<char, eys::serializer_char>(eys::address("127.0.0.1", 1234)) << 'T';
    return 0;
}