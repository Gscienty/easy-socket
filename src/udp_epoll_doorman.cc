#include "udp_epoll_doorman.h"
#include <unistd.h>

namespace eys {
    udp_epoll_doorman::udp_epoll_doorman(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , waiting_fds_count(0) {

        this->active_events = new epoll_event[size];
    }

    udp_epoll_doorman::~udp_epoll_doorman() {
        delete[] this->active_events;
        close(this->epoll_fd);
    }
    
    bool udp_epoll_doorman::reg(udp_doorman &doorman, int types) {
        epoll_event event = { 0, { 0 } };

        event.events = static_cast<int>(types);
        event.data.ptr = reinterpret_cast<void *>(&doorman);

        int ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
        if (ret < 0) {
            return false;
        }
    }

    void udp_epoll_doorman::unreg(udp_doorman &doorman) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, doorman.get_fd(), &event);
    }

    size_t udp_epoll_doorman::await(int timeout) {
        if (this->waiting_fds_count != 0) {
            return this->waiting_fds_count;
        }
        this->waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events, this->fd_count, timeout);

        return this->waiting_fds_count;
    }

    void udp_epoll_doorman::clear_waiting() {
        this->waiting_fds_count = 0;
    }

    bool udp_epoll_doorman::none_waiting() const {
        return this->waiting_fds_count == 0;
    }

    udp_doorman &udp_epoll_doorman::take() {
        return *reinterpret_cast<udp_doorman *>(this->active_events[--this->waiting_fds_count].data.ptr);
    }
}