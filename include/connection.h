#ifndef _EYS_SOCKET_
#define _EYS_SOCKET_

#include "address.h"
#include "define.h"

namespace eys {

    class connection {
    private:
        int fd;
        bool binded;
        address binded_address;

    public:
        connection(connection_type type);
        connection(connection_type type, address addr, int fd);
        virtual ~connection();

        int get_fd() const;
        bool bind_address(address &addr);
        address get_binded_address() const;
    };
}

#endif