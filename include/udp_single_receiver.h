#ifndef _EYS_UDP_SINGLE_RECEIVER_
#define _EYS_UDP_SINGLE_RECEIVER_

#include "address.h"
#include "connection.h"
#include "udp_special_remote_receiver.h"

namespace eys {
    class udp_single_receiver {
    private:
        connection conn;
        address local;
        char *buffer;
        size_t buffer_size;
    public:
        udp_single_receiver(address local, size_t buffer_size);
        virtual ~udp_single_receiver();

        template <typename E = char>
        udp_special_remote_receiver operator>> (E &e) {
            sockaddr_in remoteAddr;
            socklen_t len = sizeof(sockaddr_in);
            int truthLen = recvfrom(this->conn.get()
                                , this->buffer
                                , this->buffer_size
                                , 0
                                , (sockaddr *) &remoteAddr
                                , &len);
            
            udp_special_remote_receiver receiver = udp_special_remote_receiver(local
                                                                            , address(remoteAddr)
                                                                            , this->buffer
                                                                            , len);
            receiver >> e;
            return receiver;
        }
    };
}

#endif