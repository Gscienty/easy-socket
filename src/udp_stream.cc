#include "udp_stream.h"

namespace eys {
    udp_stream::udp_stream() : default_receive_buffer_size(1024) { }

    udp_receiver udp_stream::in(address addr) {
        return this->in(addr, this->default_receive_buffer_size);
    }

    udp_receiver udp_stream::in(address addr, size_t reveiver_buffer_size) {
        return udp_receiver(addr, reveiver_buffer_size);
    }

    udp_sender udp_stream::out(address addr) {
        return udp_sender(addr);
    }
}