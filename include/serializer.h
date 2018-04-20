#ifndef _EYS_SERIALIZER_
#define _EYS_SERIALIZER_

#include <vector>
#include <string>
#include <cstring>

#include <iostream>

namespace eys {

    template <typename E>
    struct serializer { };

    template <typename T>
    struct value_type_serializer {
        static void serialize(char *v, T e) {
            for (size_t i = 0; i < sizeof(T); i++) {
                v[i] = reinterpret_cast<char *>(&e)[sizeof(T) - 1 - i];
            }
        }
    };

    template <>
    struct serializer<char> {
        static char *serialize(char e, size_t &size) {
            size = sizeof(e);
            char *buffer = new char(size);
            value_type_serializer<char>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned char> {
        static char *serialize(unsigned char e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<unsigned char>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<short> {
        static char *serialize(short e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<short>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned short> {
        static char *serialize(unsigned char e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<unsigned short>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<int> {
        static char *serialize(int e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<int>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned int> {
        static char *serialize(unsigned int e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<unsigned int>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<long> {
        static char *serialize(long e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<long>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned long> {
        static char *serialize(unsigned long e, size_t &size) {
            size = sizeof(e);
            char *buffer(new char(size));
            value_type_serializer<unsigned long>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<std::string> {
        static char *serialize(std::string str, size_t &size) {
            size = str.length() + 1;
            char *buffer(new char[size]);
            buffer[size - 1] = 0;
            std::uninitialized_copy(str.begin(), str.end(), buffer);
            return buffer;
        }
    };

    template <>
    struct serializer<const char *> {
        static char *serialize(const char *str,  size_t &size) {
            size = strlen(str) + 1;
            char *buffer(new char[size]);
            std::uninitialized_copy(str, str + size, buffer);
            return buffer;
        }
    };
}

#endif