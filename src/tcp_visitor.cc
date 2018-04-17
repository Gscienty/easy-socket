#include "tcp_visitor.h"
#include <sys/socket.h>
#include <errno.h>
#include <iostream>

namespace eys {
    tcp_visitor::tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size)
        : in_buffer(buffer_size)
        , base_fd(conn)
        , local(local)
        , remote(remote){ }

    tcp_visitor::tcp_visitor(const tcp_visitor &visitor)
        : in_buffer(static_cast<in_buffer>(visitor))
        , base_fd(visitor.conn)
        , local(visitor.local)
        , remote(visitor.remote) { std::cout << visitor.get_fd() << std::endl; }
    
    tcp_visitor &tcp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }
    
    size_t tcp_visitor::receive(int flags) {
        this->seek = 0;
        this->data_size = recv(this->conn->get_fd(), this->buffer.get(), this->buffer_size, flags);
        if (this->data_size == -1) {
            perror(strerror(errno));
            this->data_size = 0;
        }
        return this->data_size;
    }

    tcp_sender tcp_visitor::send() {
        return tcp_sender(this->conn);
    }
}