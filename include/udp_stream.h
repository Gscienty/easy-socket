#ifndef _EYS_UDP_STREAM_
#define _EYS_UDP_STREAM_

#include "address.h"
#include "connection.h"
#include "udp_sender.h"
#include "udp_single_receiver.h"

namespace eys {
    class udp_stream {
    private:
        size_t default_receive_buffer_size;
    public:
        udp_stream();

        udp_single_receiver in(address addr);
        udp_single_receiver in(address addr, size_t reveiver_buffer_size);

        udp_sender out(address addr);
    };
}

#endif