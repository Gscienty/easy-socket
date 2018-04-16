#ifndef _EYS_EPOLL_
#define _EYS_EPOLL_

#include "define.h"
#include "base_fd.h"
#include <functional>
#include <memory>
#include <map>

namespace eys {
    struct epoll_event_struct {
        int fd;
        base_fd *ptr;
        void *callback;
        void (*func) (base_fd *fd, void *callback, int events);
    };

    class epoll {
    private:
        int epoll_fd;

        const size_t fd_count;
        std::unique_ptr<epoll_event> active_events;
        std::map<int, epoll_event_struct> fds;

    public:
        epoll(size_t size);

        template<class T>
        bool attention(T &f, const int &events, std::function<void(T &, int)> func) {
            this->fds.insert(
                std::pair<int, epoll_event_struct>(f.get_fd(), {
                    f.get_fd(),
                    reinterpret_cast<base_fd *>(&f),
                    reinterpret_cast<void *>(&func),
                    [] (base_fd *base, void *callback, int events) -> void {
                        (*reinterpret_cast<std::function<void(T &, int &)> *>(callback))(*reinterpret_cast<T *>(base), events);
                    }
                })
            );
        
            epoll_event event;
            event.events = events;
            event.data.ptr =  &this->fds[f.get_fd()];

            return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, f.get_fd(), &event) >= 0;
                        
        }

        void forget(base_fd &f);
        void await(int timeout = -1);
    };
}

#endif