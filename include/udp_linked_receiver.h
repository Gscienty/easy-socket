#ifndef _EYS_UDP_LINKED_RECEIVER_
#define _EYS_UDP_LINKED_RECEIVER_

#include "address.h"
#include "deserializer.h"

namespace eys {

    class udp_linked_receiver {
    private:
        address local;
        address remote;
        const char *&buffer;
        const size_t buffer_size;
        size_t seek;

    public:
        udp_linked_receiver(address local, address remote, const char *buffer, const size_t buffer_size);
        
        template <typename E = char, typename OP_deserializer = deserializer<E> >
        udp_linked_receiver &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer, this->buffer_size, this->seek);
            return (*this);
        }

        udp_linked_receiver &operator>> (address &addr);
        size_t remainder() const;
    };
}

#endif