#ifndef _EYS_UDP_VISITOR_
#define _EYS_UDP_VISITOR_

#include "address.h"
#include "base_fd.h"
#include "deserializer.h"
#include "udp_sender.h"
#include <memory>

namespace eys {

    class udp_visitor : public base_fd {
    private:
        std::unique_ptr<char> buffer;
        address local;
        address remote;
        size_t buffer_size;
        size_t data_size; 
        size_t seek;

    public:
        udp_visitor(address local, std::shared_ptr<connection> &conn, size_t buffer_size);
        
        fd_type get_fd_type() const { return fd_type::fd_type_udp_visitor; }

        template <typename E = char, typename OP_deserializer = deserializer<E> >
        udp_visitor &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }
        udp_visitor &operator>> (address &addr);
        size_t remainder() const;
        udp_sender send();
        udp_visitor &receive(int flags = 0);
    };
}

#endif