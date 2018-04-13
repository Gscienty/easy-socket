#ifndef _EYS_UDP_RECEIVER_
#define _EYS_UDP_RECEIVER_

#include "address.h"
#include "connection.h"
#include "udp_visitor.h"
#include <memory>

namespace eys {
    class udp_receiver {
    private:
        std::shared_ptr<connection> conn;
        std::shared_ptr<char> buffer;
        address local;
        size_t buffer_size;
    public:
        udp_receiver(address local, size_t buffer_size);

        std::shared_ptr<connection> get_connection() const;
        int get_fd() const;
        udp_visitor get_visitor();
    };
}

#endif