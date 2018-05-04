#ifndef _EYS_UDP_SENDER_
#define _EYS_UDP_SENDER_

#include "address.h"
#include "base_fd.h"
#include "bigendian_serializer.h"
#include <vector>
#include <memory>

namespace eys {
    class udp_sender : public base_fd {
    private:
        address remote;
    public:
        udp_sender(address remote)
            : base_fd(std::make_shared<connection>(* (new connection(connection_type::conn_type_udp))))
            , remote(remote) { }
        
        udp_sender(std::shared_ptr<connection> conn)
            : base_fd(conn)
            , remote(conn->get_binded_address()) { }

        udp_sender(udp_sender &&sender)
            : base_fd (sender)
            ,remote(sender.remote) { }

        fd_type get_fd_type() const { return fd_type::fd_type_udp_sender; }

        template <
            typename ElementType = char,
            typename SingleByteType = char,
            typename Serializer = eys::bigendian_serializer<SingleByteType, ElementType> >
        udp_sender &put (ElementType e) {
            size_t size;
            SingleByteType *buffer = nullptr;
            std::tie<SingleByteType [], size_t>(buffer, size) = Serializer::serialize(e);
            std::unique_ptr<SingleByteType []> bytes(buffer);
            
            sockaddr_in addr = this->remote.get();
            sendto(this->conn->get_fd(), bytes.get(), size, 0, (sockaddr *) &addr, sizeof(sockaddr_in));
            return (*this);
        }

    };
}

#endif
