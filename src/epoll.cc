#include "epoll.h"
#include <sys/epoll.h>

namespace eys {
    epoll::epoll(size_t size)
        : epoll_fd(epoll_create(size))
        , fd_count(size)
        , active_events(new epoll_event[size]) { }


    
    void epoll::forget(base_fd &f) {
        std::map<int, epoll_event_struct>::iterator it = this->fds.find(f.get_fd());
        if (it == this->fds.end()) {
            return;
        }
        this->fds.erase(it);
        epoll_event event;
        epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, f.get_fd(), &event);
    }

    void epoll::await(int timeout) {
        size_t waiting_fds_count = epoll_wait(
            this->epoll_fd, this->active_events.get(), this->fd_count, timeout);
        while(waiting_fds_count--) {
            epoll_event event = this->active_events.get()[waiting_fds_count];
            epoll_event_struct *event_struct = reinterpret_cast<epoll_event_struct *>(event.data.ptr);
            event_struct->func(event_struct->callback, event_struct, event.events);
        }
    }
}
