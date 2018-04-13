#ifndef _EYS_UDP_DOORMAN_
#define _EYS_UDP_DOORMAN_

#include "address.h"
#include "connection.h"
#include "udp_visitor.h"
#include <memory>

namespace eys {
    class udp_doorman {
    private:
        std::shared_ptr<connection> conn;
        address local;
    public:
        udp_doorman(address local);

        std::shared_ptr<connection> get_connection() const;
        int get_fd() const;
        udp_visitor get_visitor(size_t buffer_size = 1024);
    };
}

#endif