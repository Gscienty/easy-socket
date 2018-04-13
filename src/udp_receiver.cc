#include "udp_receiver.h"

namespace eys {
    udp_receiver::udp_receiver(address local, size_t buffer_size)
        : local(local)
        , conn(std::make_shared<connection>(*(new connection(connection_type::conn_type_udp))))
        , buffer_size(buffer_size)
        , buffer(std::make_shared<char>(buffer_size)) {
        this->conn->bind_address(local);
    }

    std::shared_ptr<connection> udp_receiver::get_connection() const {
        return this->conn;
    }

    int udp_receiver::get_fd() const {
        return this->conn->get_fd();
    }

    udp_visitor udp_receiver::get_visitor() {
        sockaddr_in remoteAddr;
        socklen_t len = sizeof(sockaddr_in);
        int truthLen = recvfrom(
            this->conn->get_fd(), this->buffer.get(), this->buffer_size, 0, (sockaddr *) &remoteAddr, &len);
        
        return udp_visitor(local, address(remoteAddr), this->conn, this->buffer, truthLen);
    }
}