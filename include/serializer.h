#ifndef _EYS_SERIALIZER_
#define _EYS_SERIALIZER_

#include <vector>
#include <string>
#include <cstring>
#include <memory>

namespace eys {

    template <typename E>
    struct serializer { };

    template <typename T>
    struct value_type_serializer {
        static void serialize(std::unique_ptr<char> &v, T e) {
            for (size_t i = 0; i < sizeof(T); i++) {
                v.get()[i] = reinterpret_cast<char *>(&e)[sizeof(T) - 1 - i];
            }
        }
    };

    template <>
    struct serializer<char> {
        static std::unique_ptr<char> serialize(char e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<char>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned char> {
        static std::unique_ptr<char> serialize(unsigned char e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<unsigned char>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<short> {
        static std::unique_ptr<char> serialize(short e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<short>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned short> {
        static std::unique_ptr<char> serialize(unsigned char e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<unsigned short>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<int> {
        static std::unique_ptr<char> serialize(int e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<int>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned int> {
        static std::unique_ptr<char> serialize(unsigned int e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<unsigned int>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<long> {
        static std::unique_ptr<char> serialize(long e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<long>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<unsigned long> {
        static std::unique_ptr<char> serialize(unsigned long e, size_t &size) {
            size = sizeof(e);
            std::unique_ptr<char> buffer(new char(size));
            value_type_serializer<unsigned long>::serialize(buffer, e);
            return buffer;
        }
    };

    template <>
    struct serializer<std::string> {
        static std::unique_ptr<char> serialize(std::string str, size_t &size) {
            size = str.length();
            std::unique_ptr<char> buffer(new char(size));
            std::uninitialized_copy(str.begin(), str.end(), buffer.get());
            return buffer;
        }
    };

    template <>
    struct serializer<const char *> {
        static std::unique_ptr<char> serialize(const char *str,  size_t &size) {
            size = strlen(str);
            std::unique_ptr<char> buffer(new char(size));
            std::uninitialized_copy(str, str + size, buffer.get());
            return buffer;
        }
    };
}

#endif