#ifndef _EYS_TCP_DOORMAN_
#define _EYS_TCP_DOORMAN_

#include "address.h"
#include "base_fd.h"
#include "tcp_visitor.h"

namespace eys {
    class tcp_doorman : public base_fd {
    private:
        address local;
    public:
        tcp_doorman(address local, int backlog = 20);
        tcp_doorman(tcp_doorman &doorman);

        fd_type get_fd_type() const { return fd_type::fd_type_tcp_doorman; }

        bool watch(int backlog = 20);
        tcp_visitor get_visitor(size_t buffer_size = 1024);
    };
}

#endif