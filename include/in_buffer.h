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

        template <typename ElementType = char, typename Deserializer = eys::bigendian_serializer<char, ElementType> >
        in_buffer &get(ElementType &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = Deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }

        std::pair<char *, size_t> get_range(size_t size);

        size_t remain() const;
    };
}

#endif
