#ifndef _EYS_UDP_SENDER_
#define _EYS_UDP_SENDER_

#include "address.h"
#include "connection.h"
#include "serializer.h"
#include <vector>
#include <memory>

namespace eys {
    class udp_sender {
    private:
        connection conn;
        address remote;
    public:
        udp_sender(address remote)
            : conn(connection_type::conn_type_udp)
            , remote(remote) { }

        template <typename E = char, typename OP_serializer = serializer<E> >
        udp_sender &operator<< (E e) {
            size_t size;
            std::unique_ptr<char> bytes = OP_serializer::serialize(e, size);
            sockaddr_in addr = this->remote.get();
            sendto(this->conn.get(), bytes.get(), size, 0, (sockaddr *) &addr, sizeof(sockaddr_in));
            return (*this);
        }
    };
}

#endif