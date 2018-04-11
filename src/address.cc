#include "address.h"
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace eys {
    address::address(std::string ip, short port)
        : ip(ip)
        , port(port) { }
    
    address::address(sockaddr_in addr)
        : port(htons(addr.sin_port)) {
            //this->ip = std::string(inet_ntoa(addr.sin_addr.s_addr));
        }
    
    sockaddr_in address::get() const {
        sockaddr_in ret;
        ret.sin_family = AF_INET;
        ret.sin_port = htons(this->port);
        ret.sin_addr.s_addr = inet_addr(this->ip.c_str());

        return ret;
    }
}