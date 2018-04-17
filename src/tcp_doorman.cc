#include "tcp_doorman.h"
#include <sys/socket.h>
#include <memory>
#include <errno.h>

namespace eys {
    tcp_doorman::tcp_doorman(address local, int backlog)
        : base_fd(std::make_shared<connection>(* (new connection(connection_type::conn_type_tcp))))
        , local(local) {
        if (this->get_connection()->bind_address(local) == false) {
            perror(strerror(errno));
        }
        this->watch(backlog);
    }

    bool tcp_doorman::watch(int backlog) {
        return listen(this->conn->get_fd(), backlog) == 0;
    }

    tcp_visitor tcp_doorman::get_visitor(size_t buffer_size) {
        sockaddr_in remote_addr;
        socklen_t len = sizeof(sockaddr_in);
        int remote_fd = accept(this->conn->get_fd(), (sockaddr *) &remote_addr, &len);
        
        std::shared_ptr<connection> remote_conn = std::make_shared<connection>(
                *(new connection(connection_type::conn_type_tcp, address(remote_addr), remote_fd)));

        return tcp_visitor(this->local, address(remote_addr), remote_conn, buffer_size);
    }
}