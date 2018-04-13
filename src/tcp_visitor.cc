#include "tcp_visitor.cc"

namespace eys {
    tcp_visitor::tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size)
        : buffer(new char(buffer_size))
        , conn(conn)
        , local(local)
        , remote(remote)
        , buffer_size(buffer_size)
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
}