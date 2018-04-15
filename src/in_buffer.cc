#include "in_buffer.h"

namespace eys {
    in_buffer:in_buffer(size_t buffer_size)
        : buffer(new char(buffer_size))
        , buffer_size(buffer_size)
        , data_size(0)
        , seek(0) { }

    size_t in_buffer::remain() const {
        return this->data_size - this->seek;
    }
}