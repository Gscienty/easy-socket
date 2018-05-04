#ifndef _EYS_BIG_ENDIAN_SERIALIZER_
#define _EYS_BIG_ENDIAN_SERIALIZER_

#include <stddef.h>
#include <string>
#include <utility>

namespace eys {
    template <typename SingleByteType, typename ElementType>
    struct __inl_bigendian_serializer {
        static void serialize(SingleByteType v[], ElementType e) {
            for (size_t i = 0; i < sizeof(ElementType); i++) {
                v[i]  = reinterpret_cast<SingleByteType *>(&e)[sizeof(ElementType) - 1 - i];
            }
        }

        static ElementType deserialize(SingleByteType v[], const size_t len, size_t &seek) {
            ElementType result;
            for (size_t i = 0; i < sizeof(ElementType); i++) {
                reinterpret_cast<SingleByteType *>(&result)[sizeof(ElementType) - 1 - i] = v[seek];
                seek++;
                if (seek >= len) {
                    return result;
                }
            }
            return result;
        }
    };

   
    template <typename SingleByteType, typename ElementType>
    struct bigendian_serializer {
        static std::pair<SingleByteType *, size_t> serialize(ElementType e) {
            size_t size = sizeof(ElementType);
            SingleByteType *buffer = new SingleByteType[size];
            __inl_bigendian_serializer<SingleByteType, ElementType>::serialize(buffer, e);

            return std::pair<SingleByteType *, size_t>(buffer, size);
        }

        static ElementType deserialize(SingleByteType buffer[], size_t len, size_t &seek) {
            return __inl_bigendian_serializer<SingleByteType, ElementType>::deserialize(buffer, len, seek);
        }
    };
}

#endif

