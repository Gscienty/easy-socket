#include "deserializer.h"

namespace eys {
    char deserializer_char::deserialize(const char *buffer, size_t len, size_t &seek) { return buffer[seek++]; }
}