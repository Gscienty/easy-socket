#include "tcp_visitor.h"
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

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
    
    size_t tcp_visitor::receive() {
        ssize_t data_size = read(this->conn->get_fd(), const_cast<unsigned char *>(this->buffer.data()), this->buffer_size);
        if (data_size == -1) {
            this->data_size = 0;
        }
        else {
            this->data_size = data_size;
        }
        if (this->data_size != 0) {
            this->seek = 0;
        }
        return this->data_size;
    }

    tcp_sender tcp_visitor::send() {
        return tcp_sender(this->conn);
    }
}
