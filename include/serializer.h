#ifndef _EYS_SERIALIZER_
#define _EYS_SERIALIZER_

#include <vector>
#include <string>

namespace eys {

    template <typename E>
    struct serializer { };

    template <>
    struct serializer<char> {
        static std::vector<char> serialize(char e) { 
            return std::vector<char>(1, e);
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
}

#endif