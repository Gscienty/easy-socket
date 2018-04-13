#ifndef _EYS_UDP_RECEIVER_
#define _EYS_UDP_RECEIVER_

#include "address.h"
#include "connection.h"
#include "udp_visitor.h"
#include <memory>

namespace eys {
    class udp_receiver {
    private:
        connection conn;
        address local;
        std::shared_ptr<char> buffer;
        size_t buffer_size;
    public:
        udp_receiver(address local, size_t buffer_size);

        connection &getConnection() const;
        udp_visitor get_visitor();
    };
}

#endif