#include "tcp_receiver.h"
#include <sys/socket.h>

namespace eys {
    tcp_receiver::tcp_receiver(address local, size_t buffer_size)
        : conn(connection_type::conn_type_tcp)
        , local(local)
        , default_buffer_size(buffer_size) {
        this->conn.bindAddress(local);
    }
    
    connection &tcp_receiver::getConnection() const {
        return this->conn;
    }

    bool tcp_receiver::watch(int backlog) {
        return listen(this->conn.get(), backlog) == 0;
    }
}