#ifndef _EYS_SERIALIZER_
#define _EYS_SERIALIZER_

#include <vector>

namespace eys {
    class serializer_char {
    public:
        static std::vector<char> serialize(char e) { return std::vector<char>(1, e); }
    };
}

#endif