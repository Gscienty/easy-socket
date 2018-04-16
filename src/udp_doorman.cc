#include "udp_doorman.h"

namespace eys {
    udp_doorman::udp_doorman(address local)
        : local(local)
        , base_fd(std::make_shared<connection>(*(new connection(connection_type::conn_type_udp)))) {
        this->conn->bind_address(local);
    }

    udp_visitor udp_doorman::get_visitor(size_t buffer_size) {
        return udp_visitor(local, this->conn, buffer_size);
    }

    void receive(int flags) {

    }
}