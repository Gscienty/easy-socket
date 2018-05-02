#include "udp_visitor.h"

namespace eys {
    udp_visitor::udp_visitor(address local, std::shared_ptr<connection> conn, size_t buffer_size)
        : base_fd(conn)
        , in_buffer(buffer_size)
        , local(local) { }

    udp_visitor::udp_visitor(udp_visitor &&visitor)
        : base_fd(visitor)
        , in_buffer(visitor)
        , local(visitor.local)
        , remote(visitor.remote) { }

    udp_visitor &udp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    udp_sender udp_visitor::send() {
        return udp_sender(this->conn);
    }

    size_t udp_visitor::receive(int flags) {
        sockaddr_in remote_addr;
        socklen_t len = sizeof(sockaddr_in);
        this->data_size = recvfrom(
            this->conn->get_fd(), this->buffer.get(), this->buffer_size, flags, (sockaddr *) &remote_addr, &len);
        
        this->remote = address(remote_addr);
        this->seek = 0;
        return this->data_size;
    }
}
