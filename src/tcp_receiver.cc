#include "tcp_receiver.h"
#include <sys/socket.h>

namespace eys {
    tcp_receiver::tcp_receiver(address local, size_t buffer_size)
        : conn(connection_type::conn_type_tcp)
        , local(local)
        , default_buffer_size(buffer_size) {
        this->conn.bind_address(local);
    }
    
    std::shared_ptr<connection> &tcp_receiver::get_connection() const {
        return this->conn;
    }

    bool tcp_receiver::watch(int backlog) {
        return listen(this->conn.get(), backlog) == 0;
    }

    int tcp_receiver::get_fd() const {
        return this->conn->get_fd();
    }
}