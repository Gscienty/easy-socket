#ifndef _EYS_DEFAULT_
#define _EYS_DEFAULT_

#include <sys/types.h>
#include <sys/epoll.h>

namespace eys {
    enum connection_type {
        conn_type_udp,
        conn_type_tcp
    };

    const int message_out_of_band = MSG_OOB;
    const int message_peek = MSG_PEEK;
    const int message_wait_all = MSG_WAITALL;
    const int message_dont_wait = MSG_DONTWAIT;
    const int message_dont_route = MSG_DONTROUTE;

    const int epoll_event_readable = EPOLLIN;
    const int epoll_event_writable = EPOLLOUT;
    const int epoll_event_primary = EPOLLPRI;
    const int epoll_event_error = EPOLLERR;
    const int epoll_event_edge_triggered = EPOLLET;
    const int epoll_event_one_shot = EPOLLONESHOT;
}

#endif