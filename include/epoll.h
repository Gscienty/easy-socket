#ifndef _EYS_EPOLL_
#define _EYS_EPOLL_

#include "define.h"
#include "base_fd.h"
#include <memory>
#include <map>

namespace eys {
    struct epoll_event_struct {
        int fd;
        std::shared_ptr<base_fd> arg_ptr;
        void *callback;
        void (*func) (void *callback, epoll_event_struct *args, int events);
    };

    class epoll {
    private:
        int epoll_fd;

        const size_t fd_count;
        std::unique_ptr<epoll_event> active_events;
        std::map<int, epoll_event_struct> fds;

    public:
        epoll(size_t size);

        template<class ArgumentType, class FunctionType>
        bool attention(ArgumentType &arg, const int &events, FunctionType &&func) {
            ArgumentType *inner_arg = new ArgumentType(arg);

            this->fds.insert(std::pair<int, epoll_event_struct>(inner_arg->get_fd(), {
                inner_arg->get_fd(),
                std::make_shared<ArgumentType>(*inner_arg),
                static_cast<void *>(&func),
                [] (void *callback, epoll_event_struct *arg_store, int events) -> void {
                    ArgumentType *arg = reinterpret_cast<ArgumentType *>(arg_store->arg_ptr.get());
                    (*static_cast<FunctionType *>(callback))(*arg, events);
                }
            }));
        
            epoll_event event;
            event.events = events;
            event.data.ptr =  &this->fds[inner_arg->get_fd()];

            return epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, inner_arg->get_fd(), &event) >= 0;
                        
        }

        void forget(base_fd &f);
        void await(int timeout = -1);
    };
}

#endif
