#include "base_fd.h"

namespace eys {
    base_fd::base_fd(std::shared_ptr<connection> &conn)
        : conn(conn) { }

    std::shared_ptr<connection> base_fd::get_connection() const {
        return this->conn;
    }

    int base_fd::get_fd() const {
        return this->conn.get_fd();
    }
}
