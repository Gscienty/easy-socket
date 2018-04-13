#ifndef _EYS_TCP_VISITOR_
#define _EYS_TCP_VISITOR_

#include "address.h"
#include "connection.h"
#include "deserializer.h"
#include <memory>

namespace eys {
    class tcp_visitor {
    private:
        std::unique_ptr<char> buffer;
        std::shared_ptr<connection> conn;
        address local;
        address remote;
        const size_t buffer_size;
        size_t seek;
    
    public:
        tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size);

        template <typename E = char, typename OP_deserializer = deserializer<E> >
        tcp_visitor &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }
        tcp_visitor &operator>> (address &addr);
        int get_fd() const;
        size_t remainder() const;
    };
}

#endif