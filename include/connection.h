#ifndef _EYS_SOCKET_
#define _EYS_SOCKET_

#include "address.h"

namespace eys {
    enum connection_type {
        conn_type_udp,
        conn_type_tcp
    };

    class connection {
    private:
        int fd;
        bool binded;

    public:
        connection(connection_type type);
        virtual ~connection();

        int get() const;
        bool bindAddress(address &addr);
    };
}

#endif