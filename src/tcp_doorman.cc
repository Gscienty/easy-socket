#include "tcp_doorman.h"
#include <sys/socket.h>
#include <memory>

namespace eys {
    tcp_doorman::tcp_doorman(address local, size_t buffer_size)
        : conn(std::make_shared<connection>(*(new connection(connection_type::conn_type_tcp))))
        , local(local)
        , default_buffer_size(buffer_size) {
        this->conn->bind_address(local);
    }
    
    std::shared_ptr<connection> tcp_doorman::get_connection() const {
        return this->conn;
    }

    bool tcp_doorman::watch(int backlog) {
        return listen(this->conn->get_fd(), backlog) == 0;
    }

    int tcp_doorman::get_fd() const {
        return this->conn->get_fd();
    }

    tcp_visitor tcp_doorman::get_visitor() { return this->get_visitor(this->default_buffer_size); }


    tcp_visitor tcp_doorman::get_visitor(size_t buffer_size) {
        sockaddr_in remote_addr;
        socklen_t len = sizeof(sockaddr_in);
        int remote_fd = accept(this->conn->get_fd(), (sockaddr *) &remote_addr, &len);
        
        std::shared_ptr<connection> remote_conn = std::make_shared<connection>(
                *(new connection(connection_type::conn_type_tcp, address(remote_addr), remote_fd)));

        return tcp_visitor(this->local, address(remote_addr), remote_conn, buffer_size);
    }
}