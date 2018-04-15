#ifndef _EYS_BASE_DF_
#define _EYS_BASE_DF_

#include "connection.h"
#include "define.h"
#include <memory>

namespace eys {
    class base_fd {
    private:
        std::shared_ptr<connection> conn;
    public:
        base_fd(std::shared_ptr<connection> &conn);
        virtual fd_type get_fd_type() const = 0;
        std::shared_ptr<connection> get_connection() const;
        int get_fd() const;
    };
}

#endif;