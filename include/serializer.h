#ifndef _EYS_SERIALIZER_
#define _EYS_SERIALIZER_

#include <vector>
#include <string>
#include <cstring>

namespace eys {

    template <typename E>
    struct serializer { };

    template <typename T>
    struct value_type_serializer {
        static void serialize(std::vector<char> &v, T e) {
            for (size_t i = 0; i < sizeof(T); i++) {
                v[i] = reinterpret_cast<char *>(&e)[sizeof(T) - 1 - i];
            }
        }
    };

    template <>
    struct serializer<char> {
        static std::vector<char> serialize(char e) { 
            return std::vector<char>(1, e);
        }
    };

    template <>
    struct serializer<unsigned char> {
        static std::vector<char> serialize(unsigned char e) {
            return std::vector<char>(1, *((char *) &e));
        }
    };

    template <>
    struct serializer<short> {
        static std::vector<char> serialize(short e) {
            std::vector<char> ret(2);
            value_type_serializer<short>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<unsigned short> {
        static std::vector<char> serialize(unsigned char e) {
            std::vector<char> ret(2);
            value_type_serializer<unsigned short>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<int> {
        static std::vector<char> serialize(int e) {
            std::vector<char> ret(4);
            value_type_serializer<int>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<unsigned int> {
        static std::vector<char> serialize(unsigned int e) {
            std::vector<char> ret(4);
            value_type_serializer<unsigned int>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<long> {
        static std::vector<char> serialize(long e) {
            std::vector<char> ret(8);
            value_type_serializer<long>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<unsigned long> {
        static std::vector<char> serialize(unsigned long e) {
            std::vector<char> ret(8);
            value_type_serializer<unsigned long>::serialize(ret, e);
            return ret;
        }
    };

    template <>
    struct serializer<std::string> {
        static std::vector<char> serialize(std::string str) {
            std::vector<char> ret;
            ret.assign(str.begin(), str.end());
            return ret;
        }
    };

    template <>
    struct serializer<const char *> {
        static std::vector<char> serialize(const char *str) {
            std::vector<char> ret;
            ret.assign(str, str + strlen(str));
            return ret;
        }
    };
}

#endif