#ifndef _EYS_UDP_RECEIVER_
#define _EYS_UDP_RECEIVER_

#include "address.h"
#include "connection.h"
#include "udp_linked_receiver.h"

namespace eys {
    class udp_receiver {
    private:
        connection conn;
        address local;
        char *buffer;
        size_t buffer_size;
    public:
        udp_receiver(address local, size_t buffer_size);
        virtual ~udp_receiver();

        template <typename E = char>
        udp_linked_receiver operator>> (E &e) {
            sockaddr_in remoteAddr;
            socklen_t len = sizeof(sockaddr_in);
            int truthLen = recvfrom(this->conn.get()
                                , this->buffer
                                , this->buffer_size
                                , 0
                                , (sockaddr *) &remoteAddr
                                , &len);
            
            udp_linked_receiver receiver = udp_linked_receiver(local
                                                            , address(remoteAddr)
                                                            , this->buffer
                                                            , len);
            receiver >> e;
            return receiver;
        }

        connection &getConnection();
    };
}

#endif