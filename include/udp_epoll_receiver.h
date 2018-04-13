#ifndef _EYS_UDP_EPOLL_RECEIVER_
#define _EYS_UDP_EPOLL_RECEIVER_

#include "udp_special_remote_receiver.h"
#include "udp_receiver.h"
#include <map>
#include <sys/epoll.h>

namespace eys {
        const int epoll_event_readable = EPOLLIN;
        const int epoll_event_writable = EPOLLOUT;
        const int epoll_event_primary = EPOLLPRI;
        const int epoll_event_error = EPOLLERR;
        const int epoll_event_edge_triggered = EPOLLET;
        const int epoll_event_one_shot = EPOLLONESHOT;

    class udp_epoll_receiver {
    private:
        int epoll_fd;

        const size_t fd_count;
        size_t waiting_fds_count;
        epoll_event *active_events;
    public:
        udp_epoll_receiver(size_t size);
        ~udp_epoll_receiver();

        bool reg(udp_single_receiver &receiver, int types);
        void unreg(udp_single_receiver &receiver);

        void clear_waiting();
        bool none_waiting() const;

        size_t await(int timeout = -1);

        epoll_event take();
    };
}

#endif