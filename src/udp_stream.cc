#include "udp_stream.h"

namespace eys {
    udp_stream::udp_stream() : default_receive_buffer_size(1024) { }

    udp_doorman udp_stream::receive(address addr) {
        return this->receive(addr);
    }

    udp_sender udp_stream::send(address addr) {
        return udp_sender(addr);
    }
}