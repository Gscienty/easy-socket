#include "udp_epoll_doorman.h"
#include <unistd.h>

namespace eys {
    udp_epoll_doorman::udp_epoll_doorman(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , waiting_fds_count(0)
        , active_events(new epoll_event[size]) { }

    udp_epoll_doorman::~udp_epoll_doorman() {
        close(this->epoll_fd);
    }
    
    bool udp_epoll_doorman::reg(udp_doorman &doorman, int types) {
        epoll_event event = { 0, { 0 } };

        event.events = types;
        event.data.ptr = reinterpret_cast<void *>(&doorman);

        return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
    }

    void udp_epoll_doorman::unreg(udp_doorman &doorman) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, doorman.get_fd(), &event);
    }

    void udp_epoll_doorman::await(void (*func)(udp_doorman &), int timeout) {
        this->waiting_fds_count = 0;
        this->waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events.get(), this->fd_count, timeout);
        
        while(this->waiting_fds_count--) {
            func(*reinterpret_cast<udp_doorman *>(this->active_events.get()[this->waiting_fds_count].data.ptr));
        }
    }

    void udp_epoll_doorman::clear_waiting() {
        this->waiting_fds_count = 0;
    }

    bool udp_epoll_doorman::none_waiting() const {
        return this->waiting_fds_count == 0;
    }
}