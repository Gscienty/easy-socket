#ifndef _EYS_TCP_VISITOR_
#define _EYS_TCP_VISITOR_

#include "address.h"
#include "base_fd.h"
#include "in_buffer.h"
#include "bigendian_serializer.h"
#include "tcp_sender.h"
#include <sys/types.h>

namespace eys {
    
    class tcp_visitor : public base_fd, public in_buffer {
    private:
        address local;
        address remote;
    
    public:
        tcp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const size_t buffer_size);
        tcp_visitor(const tcp_visitor &);

        fd_type get_fd_type() const { return fd_type::fd_type_tcp_visitor; }
        
        template <typename ElementType = char, typename Deserializer = eys::bigendian_serializer<char, ElementType> >
        in_buffer &get(ElementType &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = Deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }

        tcp_visitor &operator>> (address &addr);
        tcp_sender send();
        size_t receive();
    };
}

#endif
