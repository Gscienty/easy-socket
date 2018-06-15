#ifndef _EYS_IN_BUFFER_
#define _EYS_IN_BUFFER_

#include "bigendian_serializer.h"
#include <utility>
#include <string>
#include <memory>

namespace eys {
    class in_buffer {
    protected:
        std::basic_string<unsigned char> buffer;
        size_t buffer_size;
        size_t data_size;
        size_t seek;

    public:
        in_buffer(size_t buffer_size);

        template <typename SingleByteType = unsigned char, typename ElementType = char, typename Deserializer = eys::bigendian_serializer<SingleByteType, ElementType> >
        in_buffer &get(ElementType &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = Deserializer::deserialize(this->buffer, this->seek);
            return (*this);
        }
        
        template <typename SingleByteType = unsigned char>
        std::basic_string<SingleByteType> get_range(size_t size) {
            size_t truth_size = std::min<size_t>(size, this->remain());

            std::basic_string<SingleByteType> result;
            result.assign(this->buffer.begin() + this->seek, this->buffer.begin() + this->seek + truth_size);
            this->seek += truth_size;

            return result;
        }

        size_t remain() const;
    };
}

#endif
