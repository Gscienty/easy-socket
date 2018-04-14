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
        return udp_visitor(local, this->conn, buffer_size);
    }
}