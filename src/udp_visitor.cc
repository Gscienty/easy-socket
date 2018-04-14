#include "udp_visitor.h"

namespace eys {
    udp_visitor::udp_visitor(address local, std::shared_ptr<connection> &conn, size_t buffer_size)
        : local(local)
        , buffer(new char(buffer_size))
        , buffer_size(buffer_size)
        , data_size(0)
        , seek(0)
        , conn(conn) { }

    udp_visitor &udp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    size_t udp_visitor::remainder() const {
        return this->buffer_size - this->seek;
    }

    udp_sender udp_visitor::send() {
        return udp_sender(this->conn);
    }

    int udp_visitor::get_fd() const {
        return this->conn->get_fd();
    }

    udp_visitor &udp_visitor::receive(int flags) {
        sockaddr_in remote_addr;
        socklen_t len = sizeof(sockaddr_in);
        this->data_size = recvfrom(
            this->conn->get_fd(), this->buffer.get(), buffer_size, flags, (sockaddr *) &remote_addr, &len);
        
        this->remote = address(remote_addr);
        return *this;
    }
}