#ifndef _EYS_UDP_VISITOR_
#define _EYS_UDP_VISITOR_

#include "address.h"
#include "base_fd.h"
#include "in_buffer.h"
#include "udp_sender.h"


namespace eys {
    class udp_visitor : public base_fd, public in_buffer {
    private:
        address local;
        address remote;

    public:
        udp_visitor(address local, std::shared_ptr<connection> conn, size_t buffer_size);
        udp_visitor(udp_visitor &&);

        fd_type get_fd_type() const { return fd_type::fd_type_udp_visitor; }

        template <typename E = char, typename OP_deserializer = deserializer<E> >
        in_buffer &operator>> (E &e) {
            return this->get(e);
        }

        template <typename E = char, typename OP_deserializer = deserializer<E> >
        in_buffer &get(E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }

        udp_visitor &operator>> (address &addr);
        udp_sender send();
        size_t receive(int flags = 0);
    };
}

#endif