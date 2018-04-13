#include "udp_receiver.h"

namespace eys {
    udp_receiver::udp_receiver(address local, size_t buffer_size)
        : conn(connection_type::conn_type_udp)
        , local(local)
        , buffer_size(buffer_size) {
        this->buffer = new char[buffer_size];
        conn.bindAddress(local);
    }

    udp_receiver::~udp_receiver() {
        delete[] this->buffer;
    }

    connection &udp_receiver::getConnection() {
        return this->conn;
    }
}