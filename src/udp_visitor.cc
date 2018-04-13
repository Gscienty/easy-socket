#include "udp_visitor.h"

namespace eys {
    udp_visitor::udp_visitor(address local, address remote, std::shared_ptr<char> buffer, const size_t buffer_size)
        : local(local)
        , remote(remote)
        , buffer(buffer)
        , buffer_size(buffer_size)
        , seek(0) { }

    udp_visitor &udp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    size_t udp_visitor::remainder() const {
        return this->buffer_size - this->seek;
    }
}