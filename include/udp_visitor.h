#ifndef _EYS_UDP_VISITOR_
#define _EYS_UDP_VISITOR_

#include "address.h"
#include "deserializer.h"
#include <memory>

namespace eys {

    class udp_visitor {
    private:
        address local;
        address remote;
        std::shared_ptr<char> buffer;
        const size_t buffer_size;
        size_t seek;

    public:
        udp_visitor(address local, address remote, std::shared_ptr<char> buffer, const size_t buffer_size);
        
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
    };
}

#endif