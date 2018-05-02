#ifndef _EYS_TCP_SENDER_
#define _EYS_TCP_SENDER_

#include "address.h"
#include "base_fd.h"
#include "bigendian_serializer.h"

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
            typename Serializer = eys::bigendian_serializer<SingleByteType *, ElementType> >
        tcp_sender &put (ElementType e) {
            size_t size;
            SingleByteType *buffer = nullptr;
            std::tie<SingleByteType *, size_t>(buffer, size) = Serializer::serialize(e, size);
            std::unique_ptr<SingleByteType *> bytes(buffer);
            // sockaddr_in addr = this->remote.get();
            send(this->conn->get_fd(), bytes.get(), size + 1, 0);
            return (*this);
        }
    };
}

#endif
