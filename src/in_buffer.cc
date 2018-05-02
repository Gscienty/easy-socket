#include "in_buffer.h"
#include <algorithm>
#include <memory>

namespace eys {
    in_buffer::in_buffer(size_t buffer_size)
        : buffer(std::shared_ptr<char>(new char[buffer_size], std::default_delete<char[]>()))
        , buffer_size(buffer_size)
        , data_size(0)
        , seek(0) { }

    size_t in_buffer::remain() const {
        return this->data_size - this->seek;
    }
}
