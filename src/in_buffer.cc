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

    std::pair<char *, size_t> in_buffer::get_range(size_t size) {
        size_t truth_size = std::min<size_t>(size, this->remain());
        char *buffer = new char[truth_size];

        std::uninitialized_copy_n(this->buffer.get() + this->seek, truth_size, buffer);
        this->seek += truth_size;

        return std::pair<char *, size_t>(buffer, truth_size);
    }
}