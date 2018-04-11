#ifndef _EYS_UDP_STREAM_
#define _EYS_UDP_STREAM_

#include "address.h"
#include "connection.h"
#include "serializer.h"
#include "deserializer.h"

namespace eys {
    
    class udp_sender {
    private:
        connection &conn;
        address remote;
    public:
        udp_sender(connection &conn, address remote)
            : conn(conn)
            , remote(remote) { }

        template <typename E = char>
        udp_sender &operator<< (E e) {
            std::vector<char> bytes = serializer<E>::serialize(e);
            sockaddr_in addr = this->remote.get();
            sendto(this->conn.get(), bytes.data(), bytes.size(), 0, (sockaddr *) &addr, sizeof(sockaddr_in));
            return (*this);
        }
    };

    class udp_special_remote_receiver {
    private:
        address local;
        address remote;
        const char *&buffer;
        const size_t buffer_size;
        size_t seek;

    public:
        udp_special_remote_receiver(address local, address remote, const char *buffer, const size_t buffer_size)
            : local(local)
            , remote(remote)
            , buffer(buffer)
            , buffer_size(buffer_size)
            , seek(0) { }
        
        template <typename E = char>
        udp_special_remote_receiver &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = deserializer<E>::deserialize(this->buffer, this->buffer_size, this->seek);
            return (*this);
        }
    };
    
    class udp_receiver {
    private:
        connection &conn;
        address local;
        char *buffer;
        size_t buffer_size;
    public:
        udp_receiver(connection &conn, address local, size_t buffer_size);
        virtual ~udp_receiver();

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
            
            udp_special_remote_receiver receiver = udp_special_remote_receiver(
                    local,
                    address(remoteAddr),
                    this->buffer,
                    len);
                    
            receiver >> e;
            return receiver;
        }
    };

    class udp_stream {
    private:
        connection conn;
        size_t receive_buffer_size;
    public:
        udp_stream();

        udp_sender operator<< (address addr) {
            return udp_sender(this->conn, addr);
        }

        udp_receiver operator>> (address addr) {
            return udp_receiver(this->conn, addr, this->receive_buffer_size);
        }
    };
}

#endif