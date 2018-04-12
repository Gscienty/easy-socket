#include "udp_receiver.h"

namespace eys {
    udp_single_receiver::udp_single_receiver(address local, size_t buffer_size)
        : conn(connection_type::conn_type_udp)
        , local(local)
        , buffer_size(buffer_size) {
        this->buffer = new char[buffer_size];
        conn.bindAddress(local);
    }

    udp_single_receiver::~udp_single_receiver() {
        delete[] this->buffer;
    }
}