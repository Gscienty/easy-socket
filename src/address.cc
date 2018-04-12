#include "address.h"
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace eys {
    address::address(std::string ip, short port)
        : ip(ip)
        , port(port) {
        
        this->sample_addr.sin_family = AF_INET;
        this->sample_addr.sin_port = htons(this->port);
        this->sample_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    }
    
    address::address(sockaddr_in addr)
        : ip(inet_ntoa(addr.sin_addr))
        , port(htons(addr.sin_port)) {
        this->sample_addr = addr;
    }
    
    sockaddr_in address::get() const {
        return this->sample_addr;
    }
}