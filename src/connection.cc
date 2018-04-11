#include "connection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace eys {
    connection::connection(connection_type type) {
        int t;
        switch (type) {
        case connection_type::conn_type_tcp:
            t = SOCK_STREAM;
            break;
        case connection_type::conn_type_udp:
            t = SOCK_DGRAM;
            break;    
        }
        
        this->fd = socket(AF_INET, t, 0);
    }

    connection::~connection() {
        close(this->fd);
    }
}