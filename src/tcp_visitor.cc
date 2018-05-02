#include "tcp_visitor.h"
#include <sys/socket.h>
#include <errno.h>

namespace eys {
    tcp_visitor::tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size)
        : base_fd(conn)
        , in_buffer(buffer_size)
        , local(local)
        , remote(remote){ }

    tcp_visitor::tcp_visitor(const tcp_visitor &visitor)
        : base_fd(visitor.conn)
        , in_buffer(visitor)
        , local(visitor.local)
        , remote(visitor.remote) { }
    
    tcp_visitor &tcp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }
    
    size_t tcp_visitor::receive(int flags) {
        this->seek = 0;
        int data_size = recv(this->conn->get_fd(), this->buffer.get(), this->buffer_size, flags);
        if (data_size == -1) {
            // TODO echo error
            // perror(strerror(errno));
            this->data_size = 0;
        }
        this->data_size = data_size;
        return this->data_size;
    }

    tcp_sender tcp_visitor::send() {
        return tcp_sender(this->conn);
    }
}
