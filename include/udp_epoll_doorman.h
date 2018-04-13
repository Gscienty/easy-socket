#ifndef _EYS_UDP_EPOLL_DOORMAN_
#define _EYS_UDP_EPOLL_DOORMAN_

#include "udp_visitor.h"
#include "udp_doorman.h"
#include <map>
#include <sys/epoll.h>

namespace eys {

    const int epoll_event_readable = EPOLLIN;
    const int epoll_event_writable = EPOLLOUT;
    const int epoll_event_primary = EPOLLPRI;
    const int epoll_event_error = EPOLLERR;
    const int epoll_event_edge_triggered = EPOLLET;
    const int epoll_event_one_shot = EPOLLONESHOT;

    class udp_epoll_doorman {
    private:
        int epoll_fd;

        const size_t fd_count;
        size_t waiting_fds_count;
        epoll_event *active_events;
    public:
        udp_epoll_doorman(size_t size);
        ~udp_epoll_doorman();

        bool reg(udp_doorman &doorman, int types);
        void unreg(udp_doorman &doorman);

        void clear_waiting();
        bool none_waiting() const;

        size_t await(int timeout = -1);

        udp_doorman &take();
    };
}

#endif