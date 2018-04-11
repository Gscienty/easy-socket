#ifndef _EYS_ADDRESS_
#define _EYS_ADDRESS_

#include <string>
#include <netinet/in.h>

namespace eys {
    class address {
    private:
        std::string ip;
        short port;
    public:
        address(std::string ip, short port);

        sockaddr_in get() const;
    };
}

#endif