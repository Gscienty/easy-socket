#ifndef _EYS_TCP_LINKED_RECEIVER_
#define _EYS_TCP_LINKED_RECEIVER_

#include "address.h"
#include "connection.h"
#include <memory>

namespace eys {
    class tcp_visitor {
    private:
        connection conn;
        std::shared_ptr<char> buffer;
    public:
    };
}

#endif