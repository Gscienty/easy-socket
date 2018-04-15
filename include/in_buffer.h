#ifndef _EYS_IN_BUFFER_
#define _EYS_IN_BUFFER_

#include "deserializer.h"
#include <memory>

namespace eys {
    class in_buffer {
    private:
        std::unique_ptr<char> buffer;
        size_t buffer_size;
        size_t data_size;
        size_t seek;

    public:
        in_buffer(size_t buffer_size);

        template <typename E = char, typename OP_deserializer = deserializer<E> >
        in_buffer &operator>> (E &e) {
            if (this->seek >= this->buffer_size) {
                return (*this);
            }
            e = OP_deserializer::deserialize(this->buffer.get(), this->buffer_size, this->seek);
            return (*this);
        }

        size_t remain() const;
        virtual void receive(int flags = 0) = 0;
    };
}

#endif