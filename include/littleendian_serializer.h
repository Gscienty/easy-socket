#ifndef _EYS_LITTLE_ENDIAN_SERIALIZER_
#define _EYS_LITTLE_ENDIAN_SERIALIZER_

#include <stddef.h>
#include <utility>

namespace eys {
    template <typename BufferType, typename ElementType>
    static void __inl_littleendian_serialize(BufferType v, ElementType e) {
        for (size_t i = 0; i < sizeof(ElementType); i++) {
            v[i] = reinterpret_cast<BufferType>(&e)[i];
        }
    }

    template <typename BufferType, typename ElementType>
    static void __inl_littleendian_deserialize(
            const BufferType v, const size_t len, size_t &seek) {
        ElementType result;
        for (size_t i = 0; i < sizeof(ElementType); i++) {
            reinterpret_cast<BufferType>(&result)[i] = v[seek];
            seek++;
            if (seek >= len) {
                return result;
            }
        }
        return result;
    }

    template <typename SingleByteType, typename ElementType>
    struct littleendian_serializer {
        static std::pair<SingleByteType *, size_t> serialize(ElementType e) {
            size_t size = sizeof(ElementType);
            SingleByteType *buffer = new SingleByteType[size];
            __inl_littleendian_serialize(buffer, e);
            return std::pair<SingleByteType *, size_t>(buffer, size);
        }
        static ElementType deserialize(
                const SingleByteType *buffer, size_t len, size_t &seek) {
            return __inl_littleendian_deserialize<SingleByteType *, ElementType>(buffer, len, seek);
        }
    };
}

#endif
