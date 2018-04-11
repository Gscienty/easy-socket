#ifndef _EYS_UDP_STREAM_
#define _EYS_UDP_STREAM_

#include "address.h"
#include "connection.h"
#include "serializer.h"

namespace eys {
    template <typename E = char, class OP_serializer = serializer_char>
    class udp_sender : protected connection {
    private:
        address remote;
    public:
        udp_sender(address remote)
        : connection(connection_type::conn_type_udp)
        , remote(remote) { }

        udp_sender<E, OP_serializer> &operator<< (E e) {
            std::vector<char> bytes = OP_serializer::serialize(e);
            sockaddr_in addr = this->remote.get();
            sendto(this->fd, bytes.data(), bytes.size(), 0, (sockaddr *) &addr, sizeof(sockaddr_in));
            return (*this);
        }
    };

    class udp_stream {
        
    };
}

#endif