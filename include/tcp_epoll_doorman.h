#ifndef _EYS_TCP_EPOLL_DOORMAN_
#define _EYS_TCP_EPOLL_DOORMAN_

#include "tcp_visitor.h"
#include "tcp_doorman.h"
#include "define.h"
#include <sys/epoll.h>
#include <memory>

namespace eys {
    enum tcp_epoll_type {
        tcp_type_doorman,
        tcp_type_visitor
    };

    class tcp_epoll_doorman {
    private:
        int epoll_fd;

        const size_t fd_count;
        size_t waiting_fds_count;
        std::unique_ptr<epoll_event> active_events;
    public:
        tcp_epoll_doorman(size_t size);
        ~tcp_epoll_doorman();

        bool reg(tcp_doorman &doorman, int types);
        void unreg(tcp_doorman &doorman);

        bool reg(tcp_visitor &visitor, int types);
        void unreg(tcp_visitor &visitor);

        void clean_waiting();
        bool none_waiting() const;

        size_t await(void (*doorman_func)(tcp_doorman &), void (*visitor_func)(tcp_visitor &), int timeout = -1);
    };
}

#endif