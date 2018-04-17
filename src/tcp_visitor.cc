#include "tcp_visitor.h"
#include <sys/socket.h>

namespace eys {
    tcp_visitor::tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size)
        : in_buffer(buffer_size)
        , base_fd(conn)
        , local(local)
        , remote(remote){ }
    
    tcp_visitor &tcp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }
    
    size_t tcp_visitor::receive(int flags) {
        this->data_size = recv(this->conn->get_fd(), this->buffer.get(), this->buffer_size, flags);
        return this->data_size;
    }

    tcp_sender tcp_visitor::send() {
        return tcp_sender(this->conn);
    }
}