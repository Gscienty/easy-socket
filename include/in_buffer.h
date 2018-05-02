#ifndef _EYS_IN_BUFFER_
#define _EYS_IN_BUFFER_

#include "bigendian_serializer.h"
#include <utility>
#include <memory>

namespace eys {
    class in_buffer {
    protected:
        std::shared_ptr<char> buffer;
        size_t buffer_size;
        size_t data_size;
        size_t seek;

    public:
        in_buffer(size_t buffer_size);

        template <typename SingleByteType = char, typename ElementType = char, typename Deserializer = eys::bigendian_serializer<SingleByteType, ElementType> >
        in_buffer &get(ElementType &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = Deserializer::deserialize(reinterpret_cast<SingleByteType *>(this->buffer.get()), this->buffer_size, this->seek);
            return (*this);
        }
        
        template <typename SingleByteType = char>
        std::pair<SingleByteType *, size_t> get_range(size_t size) {
            size_t truth_size = std::min<size_t>(size, this->remain());
            SingleByteType *buffer = new SingleByteType[truth_size];

            std::copy(this->buffer.get() + this->seek, this->buffer.get() + this->seek + truth_size, reinterpret_cast<char *>(buffer));

            return std::pair<SingleByteType *, size_t>(buffer, truth_size);
        }

        size_t remain() const;
    };
}

#endif
