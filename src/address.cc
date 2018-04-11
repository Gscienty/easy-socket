#include "address.h"
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace eys {
    address::address(std::string ip, short port)
        : ip(ip)
        , port(port) { }
    
    sockaddr_in address::get() const {
        sockaddr_in ret;
        ret.sin_family = AF_INET;
        ret.sin_port = htons(this->port);
        ret.sin_addr.s_addr = inet_addr(this->ip.c_str());

        return ret;
    }
}