#ifndef _EYS_TCP_DOORMAN_
#define _EYS_TCP_DOORMAN_

#include "address.h"
#include "connection.h"
#include "tcp_visitor.h"
#include <memory>

namespace eys {
    class tcp_doorman {
    private:
        std::shared_ptr<connection> conn;
        address local;
    public:
        tcp_doorman(address local, int backlog = 20);

        std::shared_ptr<connection> get_connection() const;
        bool watch(int backlog = 20);
        int get_fd() const;
        tcp_visitor get_visitor(size_t buffer_size = 1024);
    };
}

#endif