#include "udp_doorman.h"

namespace eys {
    udp_doorman::udp_doorman(address local)
        : local(local)
        , conn(std::make_shared<connection>(*(new connection(connection_type::conn_type_udp)))) {
        this->conn->bind_address(local);
    }

    std::shared_ptr<connection> udp_doorman::get_connection() const {
        return this->conn;
    }

    int udp_doorman::get_fd() const {
        return this->conn->get_fd();
    }

    udp_visitor udp_doorman::get_visitor(size_t buffer_size) {
        char *buffer = new char(buffer_size);

        sockaddr_in remote_addr;
        socklen_t len = sizeof(sockaddr_in);
        size_t data_size = recvfrom(
            this->conn->get_fd(), buffer, buffer_size, 0, (sockaddr *) &remote_addr, &len);
        
        return udp_visitor(local, address(remote_addr), this->conn, buffer, data_size);
    }
}