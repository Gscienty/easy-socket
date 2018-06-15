#ifndef _EYS_BIG_ENDIAN_SERIALIZER_
#define _EYS_BIG_ENDIAN_SERIALIZER_

#include <stddef.h>
#include <string>
#include <utility>

namespace eys {
    template <typename SingleByteType, typename ElementType>
    struct __inl_bigendian_serializer {
        static void serialize(std::basic_string<SingleByteType> &buffer, ElementType e) {
            buffer.resize(sizeof(ElementType));
            for (size_t i = 0; i < sizeof(ElementType); i++) {
                buffer[i]  = reinterpret_cast<SingleByteType *>(&e)[sizeof(ElementType) - 1 - i];
            }
        }

        static ElementType deserialize(const std::basic_string<SingleByteType> &buffer, size_t &seek) {
            ElementType result;
            for (size_t i = 0; i < sizeof(ElementType); i++) {
                reinterpret_cast<SingleByteType *>(&result)[sizeof(ElementType) - 1 - i] = buffer[seek];
                seek++;
                if (seek >= buffer.size()) {
                    return result;
                }
            }
            return result;
        }
    };

   
    template <typename SingleByteType, typename ElementType>
    struct bigendian_serializer {
        static std::basic_string<SingleByteType> serialize(ElementType e) {
            std::basic_string<SingleByteType> buffer;
            __inl_bigendian_serializer<SingleByteType, ElementType>::serialize(buffer, e);

            return buffer;
        }

        static ElementType deserialize(const std::basic_string<SingleByteType> &buffer, size_t &seek) {
            return __inl_bigendian_serializer<SingleByteType, ElementType>::deserialize(buffer, seek);
        }
    };
}

#endif

