#include "tcp_epoll.h"
#include <unistd.h>
#include <utility>

namespace eys {
    tcp_epoll::tcp_epoll(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , waiting_fds_count(0)
        , active_events(new char(size)) { }

    tcp_epoll::~tcp_epoll() {
        close(this->epoll_fd);
    }
    
    bool tcp_epoll::reg(tcp_doorman &doorman, int types) {
        epoll_event event = { 0, { 0 } };
        event.events = types;
        event.data.ptr = reinterpret_cast<void *>(
            new std::pair<tcp_epoll_type, void *>(tcp_epoll_type::tcp_type_doorman, reinterpret_cast<void *>(&doorman)));

        return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
    }
    
    void tcp_epoll::unreg(tcp_doorman &doorman) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, doorman.get_fd(), &event);
        delete event.data.ptr;
    }

    bool tcp_epoll::reg(tcp_visitor &visitor, int types) {
        event.events = types;
        event.data.ptr = reinterpret_cast<void *>(
            new std::pair<tcp_epoll_type, void *>(tcp_epoll_type::tcp_type_visitor, reinterpret_cast<void *>(&visitor)));

        return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
    }

    void tcp_epoll::unreg(tcp_visitor &visitor) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, visitor.get_fd(), &event);
        delete event.data.ptr;
    }

    void tcp_epoll::clean_waiting() {
        this->waiting_fds_count = 0;
    }

    bool tcp_epoll::none_waiting() const {
        return this->waiting_fds_count == 0;
    }

    void tcp_epoll::await(void (*doorman_func)(tcp_doorman &. int), void (*visitor_func)(tcp_visitor &, int), int timeout = -1) {
        this->waiting_fds_count = 0;
        this->waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events.get(), this->fd_count, timeout);
        
        while(this->waiting_fds_count--) {
            epoll_event event = this->active_events.get()[this->waiting_fds_count];

            std::pair<tcp_epoll_type, void *> &tuple = *reinterpret_cast<std::pair<tcp_epoll_type, void *> *>(event.data.ptr);
            
            switch (tuple.first) {
            case tcp_epoll_type::tcp_type_doorman:
                doorman_func(*reinterpret_cast<tcp_doorman *>(tuple.second), event.events);
                break;
            case tcp_epoll_type::tcp_type_visitor:
                visitor_func(*reinterpret_cast<tcp_visitor * >(tuple.second), event.events);
            }
        }
    }
}