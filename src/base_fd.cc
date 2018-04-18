#include "base_fd.h"
#include <sys/fcntl.h>

namespace eys {
    base_fd::base_fd(std::shared_ptr<connection> conn)
        : conn(conn) { }

    base_fd::base_fd(base_fd &fd)
        : conn(fd.conn) { }

    bool base_fd::set_non_block() {
        return fcntl(this->conn->get_fd(), F_SETFD, O_NONBLOCK) == 0;
    }

    bool base_fd::set_async() {
        return fcntl(this->conn->get_fd(), F_SETFD, O_ASYNC) == 0;
    }

    std::shared_ptr<connection> base_fd::get_connection() const {
        return this->conn;
    }

    int base_fd::get_fd() const {
        return this->conn->get_fd();
    }
}
