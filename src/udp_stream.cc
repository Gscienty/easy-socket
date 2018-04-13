#include "udp_stream.h"

namespace eys {
    udp_stream::udp_stream() : default_receive_buffer_size(1024) { }

    udp_receiver udp_stream::receive(address addr) {
        return this->receive(addr, this->default_receive_buffer_size);
    }

    udp_receiver udp_stream::receive(address addr, size_t reveiver_buffer_size) {
        return udp_receiver(addr, reveiver_buffer_size);
    }

    udp_sender udp_stream::send(address addr) {
        return udp_sender(addr);
    }
}