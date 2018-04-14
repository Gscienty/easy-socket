#include "tcp_epoll_doorman.h"
#include <unistd.h>
#include <utility>

namespace eys {
    tcp_epoll_doorman::tcp_epoll_doorman(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , waiting_fds_count(0)
        , active_events(new char(size)) { }

    tcp_epoll_doorman::~tcp_epoll_doorman() {
        close(this->epoll_fd);
    }
    
    bool tcp_epoll_doorman::reg(tcp_doorman &doorman, int types) {
        epoll_event event = { 0, { 0 } };
        event.events = types;
        event.data.ptr = reinterpret_cast<void *>(
            new std::pair<tcp_epoll_type, void *>(tcp_epoll_type::tcp_type_doorman, reinterpret_cast<void *>(&doorman)));

        return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
    }
    
    void tcp_epoll_doorman::unreg(tcp_doorman &doorman) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, doorman.get_fd(), &event);
    }

    bool tcp_epoll_doorman::reg(tcp_visitor &visitor, int types) {
        event.events = types;
        event.data.ptr = reinterpret_cast<void *>(
            new std::pair<tcp_epoll_type, void *>(tcp_epoll_type::tcp_type_visitor, reinterpret_cast<void *>(&visitor)));

        return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, doorman.get_fd(), &event) >= 0;
    }

    void tcp_epoll_doorman::unreg(tcp_visitor &visitor) {
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, visitor.get_fd(), &event);
    }

    void tcp_epoll_doorman::clean_waiting() {
        this->waiting_fds_count = 0;
    }

    bool tcp_epoll_doorman::none_waiting() const {
        return this->waiting_fds_count == 0;
    }

    size_t tcp_epoll_doorman::await(void (*doorman_func)(tcp_doorman &), void (*visitor_func)(tcp_visitor &), int timeout = -1) {
        this->waiting_fds_count = 0;
        this->waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events.get(), this->fd_count, timeout);
        
        while(this->waiting_fds_count--) {
            std::pair<tcp_epoll_type, void *> &tuple = *reinterpret_cast<std::pair<tcp_epoll_type, void *> *>(
                this->active_events.get()[this->waiting_fds_count].data.ptr);
            
            switch (tuple.first) {
            case tcp_epoll_type::tcp_type_doorman:
                doorman_func(*reinterpret_cast<tcp_doorman *>(tuple.second));
                break;
            case 
            }
        }
    }
}