#include "udp_receiver.h"

namespace eys {
    udp_receiver::udp_receiver(address local, size_t buffer_size)
        : conn(connection_type::conn_type_udp)
        , local(local)
        , buffer_size(buffer_size) {
        this->buffer = std::make_shared<char>(buffer_size);
        conn.bindAddress(local);
    }

    connection &udp_receiver::getConnection() const {
        return this->conn;
    }

    udp_visitor udp_receiver::get_visitor() {
        sockaddr_in remoteAddr;
        socklen_t len = sizeof(sockaddr_in);
        int truthLen = recvfrom(
            this->conn.get(), this->buffer.get(), this->buffer_size, 0, (sockaddr *) &remoteAddr, &len);
        
        return udp_visitor(local, address(remoteAddr), this->buffer, truthLen);
    }
}