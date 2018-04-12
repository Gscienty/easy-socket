#ifndef _EYS_UDP_RECEIVER_
#define _EYS_UDP_RECEIVER_

#include "address.h"
#include "deserializer.h"

namespace eys {

    class udp_special_remote_receiver {
    private:
        address local;
        address remote;
        const char *&buffer;
        const size_t buffer_size;
        size_t seek;

    public:
        udp_special_remote_receiver(address local, address remote, const char *buffer, const size_t buffer_size)
            : local(local)
            , remote(remote)
            , buffer(buffer)
            , buffer_size(buffer_size)
            , seek(0) { }
        
        template <typename E = char, typename OP_deserializer = deserializer<E> >
        udp_special_remote_receiver &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer, this->buffer_size, this->seek);
            return (*this);
        }
    };
}

#endif