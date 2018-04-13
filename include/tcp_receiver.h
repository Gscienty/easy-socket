#ifndef _EYS_TCP_RECEIVER_
#define _EYS_TCP_RECEIVER_

#include "address.h"
#include "connection.h"
#include <memory>

namespace eys {
    class tcp_receiver {
    private:
        connection conn;
        address local;
        size_t default_buffer_size;
    public:
        tcp_receiver(address local, size_t buffer_size);

        std::shared_ptr<connection> get_connection() const;
        bool watch(int backlog = 20);
        int get_fd() const;
    };
}

#endif