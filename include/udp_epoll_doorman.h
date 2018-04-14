#ifndef _EYS_UDP_EPOLL_DOORMAN_
#define _EYS_UDP_EPOLL_DOORMAN_

#include "udp_visitor.h"
#include "udp_doorman.h"
#include "define.h"
#include <sys/epoll.h>
#include <memory>

namespace eys {

    class udp_epoll_doorman {
    private:
        int epoll_fd;

        const size_t fd_count;
        size_t waiting_fds_count;
        std::unique_ptr<epoll_event> active_events;
    public:
        udp_epoll_doorman(size_t size);
        ~udp_epoll_doorman();

        bool reg(udp_doorman &doorman, int types);
        void unreg(udp_doorman &doorman);

        void clear_waiting();
        bool none_waiting() const;

        void await(void (*func)(udp_doorman &), int timeout = -1);
    };
}

#endif