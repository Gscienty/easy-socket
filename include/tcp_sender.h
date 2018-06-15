#ifndef _EYS_TCP_SENDER_
#define _EYS_TCP_SENDER_

#include "address.h"
#include "base_fd.h"
#include "bigendian_serializer.h"
#include <unistd.h>

namespace eys {
    class tcp_sender : public base_fd {
    private:
        address remote;
    public:
        tcp_sender(address remote);
        tcp_sender(std::shared_ptr<connection> conn);
        tcp_sender(tcp_sender &&sender)
            : base_fd(sender)
            , remote(sender.remote) { }

        fd_type get_fd_type() const { return fd_type::fd_type_tcp_sender; }

        template <
            typename ElementType = char,
            typename SingleByteType = char,
            typename Serializer = eys::bigendian_serializer<SingleByteType, ElementType> >
        tcp_sender &put (ElementType e) {
            // serialize element
            std::basic_string<SingleByteType> buffer = Serializer::serialize(e);
            
            write(this->conn->get_fd(), buffer.data(), buffer.size());
            return (*this);
        }
    };
}

#endif
