#include "connection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace eys {
    connection::connection(connection_type type)
        : binded(false) {
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

    int connection::get_fd() const {
        return this->fd;
    }

    bool connection::bind_address(address &local) {
        if (this->binded == true) {
            return false;
        }

        sockaddr_in addr = local.get();
        int isSuccess = bind(this->fd, (sockaddr *) &addr, sizeof(sockaddr_in));
        this->binded = isSuccess == 0;
        return this->binded;
    }
}