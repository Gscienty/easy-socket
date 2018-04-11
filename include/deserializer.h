#ifndef _EYS_DESERIALIZER_
#define _EYS_DESERIALIZER_

#include <vector>
#include <string>

namespace eys {
    template <typename E>
    struct deserializer { static E deserialize(const char *buffer, size_t len, size_t &seek); };

    template<>
    struct deserializer<char> {
        static char deserialize(const char *buffer, size_t len, size_t &seek) {
            return buffer[seek++];
        }
    };
}

#endif