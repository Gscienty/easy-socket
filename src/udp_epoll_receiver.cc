#include "udp_epoll_receiver.h"
#include <unistd.h>

namespace eys {
    udp_epoll_receiver::udp_epoll_receiver(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , waiting_fds_count(0) {

        this->active_events = new epoll_event[size];        
    }

    udp_epoll_receiver::~udp_epoll_receiver() {
        delete[] this->active_events;
        close(this->epoll_fd);
    }
    
    bool udp_epoll_receiver::reg(udp_receiver &receiver, int types) {
        epoll_event event = { 0, { 0 } };

        event.events = static_cast<int>(types);
        event.data.ptr = reinterpret_cast<void *>(&receiver);

        int ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, receiver.get_fd(), &event) >= 0;
        if (ret < 0) {
            return false;
        }
    }

    void udp_epoll_receiver::unreg(udp_receiver &receiver) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, receiver.get_fd(), &event);
    }

    size_t udp_epoll_receiver::await(int timeout) {
        if (this->waiting_fds_count != 0) {
            return this->waiting_fds_count;
        }
        this->waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events, this->fd_count, timeout);

        return this->waiting_fds_count;
    }

    void udp_epoll_receiver::clear_waiting() {
        this->waiting_fds_count = 0;
    }

    bool udp_epoll_receiver::none_waiting() const {
        return this->waiting_fds_count == 0;
    }

    udp_receiver &udp_epoll_receiver::take() {
        return *reinterpret_cast<udp_receiver *>(this->active_events[--this->waiting_fds_count].data.ptr);
    }
}