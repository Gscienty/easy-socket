#ifndef _EYS_UDP_DOORMAN_
#define _EYS_UDP_DOORMAN_

#include "address.h"
#include "base_fd.h"
#include "connection.h"
#include "udp_visitor.h"

namespace eys {
    class udp_doorman : public base_fd {
    private:
        address local;
    public:
        udp_doorman(address local);

        fd_type get_fd_type() const { return fd_type::fd_type_udp_doorman; }

        udp_visitor get_visitor(size_t buffer_size = 1024);
    };
}

#endif