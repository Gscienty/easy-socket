#ifndef _EYS_SOCKET_
#define _EYS_SOCKET_

namespace eys {
    enum connection_type {
        conn_type_udp,
        conn_type_tcp
    };

    class connection {
    protected:
        int fd;
    public:
        connection(connection_type type);
        virtual ~connection();
    };
}

#endif