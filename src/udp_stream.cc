#include "udp_stream.h"

namespace eys {
    udp_receiver::udp_receiver(connection &conn, address local, size_t buffer_size)
        : conn(conn)
        , local(local)
        , buffer_size(buffer_size) {
        this->buffer = new char[buffer_size];
        sockaddr_in addr = local.get();
        bind(conn.get(), (sockaddr *) &addr, sizeof(sockaddr_in));
    }

    udp_receiver::~udp_receiver() {
        delete[] this->buffer;
    }

    udp_stream::udp_stream()
        : conn(connection_type::conn_type_udp)
        , receive_buffer_size(1024) { }
}