#ifndef _EYS_TCP_SENDER_
#define _EYS_TCP_SENDER_

#include "address.h"
#include "connection.h"
#include "serializer.h"
#include <memory>

namespace eys {
    class tcp_sender {
    private:
        std::shared_ptr<connection> conn;
        address remote;
    public:
        tcp_sender(address remote);
        tcp_sender(std::shared_ptr<connection> conn);

        template <typename E = char, typename OP_serializer = serializer<E> >
        tcp_sender &operator<< (E e) {
            size_t size;
            std::unique_ptr<char> bytes = OP_serializer::serialize(e, size);
            sockaddr_in addr = this->remote.get();
            send(this->conn->get_fd(), bytes.get(), size, 0);
            return (*this);
        }
    };
}

#endif