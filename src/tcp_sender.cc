#include "tcp_sender.h"
#include <sys/socket.h>
#include <netinet/in.h>

namespace eys {

    tcp_sender::tcp_sender(address remote)
        : conn(std::make_shared<connection>(* (new connection(connection_type::conn_type_tcp))))
        , remote(remote) {
        this->conn->bind_address(remote);

        sockaddr_in addr = remote.get();
        connect(this->conn->get_fd(), (sockaddr *) &addr, sizeof(sockaddr_in));
    }


    tcp_sender::tcp_sender(std::shared_ptr<connection> conn)
        : conn(conn)
        , remote(conn->get_binded_address()) { }
}