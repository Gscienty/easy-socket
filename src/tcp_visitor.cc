#include "tcp_visitor.h"
#include <sys/socket.h>

namespace eys {
    tcp_visitor::tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size)
        : buffer(new char(buffer_size))
        , conn(conn)
        , local(local)
        , remote(remote)
        , buffer_size(buffer_size)
        , data_size(0)
        , seek(0) { }
    
    tcp_visitor &tcp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    size_t tcp_visitor::remainder() const {
        return this->buffer_size - this->seek;
    }

    int tcp_visitor::get_fd() const {
        return this->conn->get_fd();
    }
    
    tcp_visitor &tcp_visitor::receive(int flags) {
        this->data_size = recv(this->conn->get_fd(), this->buffer.get(), this->buffer_size, flags);
        return *this;
    }

    tcp_sender tcp_visitor::send() {
        return tcp_sender(this->conn);
    }
}