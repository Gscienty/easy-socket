#ifndef _EYS_DESERIALIZER_
#define _EYS_DESERIALIZER_

#include <vector>
#include <string>

namespace eys {
    template <typename E>
    struct deserializer { static E deserialize(const char *buffer, size_t len, ssize_t &seek); };

    template <typename T>
    struct value_type_deserializer {
        static T deserialize(const char *v, const size_t len, ssize_t &seek) {
            T ret;
            for (int i = 0; i < sizeof(T); i++) {
                reinterpret_cast<char *>(&ret)[sizeof(T) - 1 - i] = v[seek];
                seek++;
                if (seek >= len) {
                    return ret;
                }
            }
            return ret;
        }
    };

    template <>
    struct deserializer<char> {
        static char deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return buffer[seek++];
        }
    };

    template <>
    struct deserializer<unsigned char> {
        static unsigned char deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return (unsigned char) *(unsigned char *) &buffer[seek++];
        }
    };

    template <>
    struct deserializer<short> {
        static short deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<short>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<unsigned short> {
        static unsigned short deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<unsigned short>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<int> {
        static int deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<int>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<unsigned int> {
        static unsigned int deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<unsigned int>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<long> {
        static long deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<long>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<unsigned long> {
        static unsigned long deserialize(const char *buffer, size_t len, ssize_t &seek) {
            return value_type_deserializer<unsigned long>::deserialize(buffer, len, seek);
        }
    };

    template <>
    struct deserializer<std::string> {
        static std::string deserialize(const char *buffer, size_t len, ssize_t &seek) {
            if (seek > len) { return std::string(); }
            std::string ret = std::string(buffer + seek, len - seek);
            seek = len;
            return ret;
        }
    };
}

#endif