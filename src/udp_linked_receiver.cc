#include "udp_linked_receiver.h"

namespace eys {
    udp_linked_receiver::udp_linked_receiver(address local, address remote, const char *buffer, const size_t buffer_size)
        : local(local)
        , remote(remote)
        , buffer(buffer)
        , buffer_size(buffer_size)
        , seek(0) { }

    udp_linked_receiver &udp_linked_receiver::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    size_t udp_linked_receiver::remainder() const {
        return this->buffer_size - this->seek;
    }
}