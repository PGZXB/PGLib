#ifndef __PGFWD_H__
#define __PGFWD_H__
#include <vector>
#include <cstdint>

namespace pg::base {
    struct FileOpenMode {
        enum Mode {
            Read = 01,
            Write = 02,
            Binary = 04,
            Append = 010,
        };
    };
} // namespace pg::base


namespace pg::type {

    typedef unsigned char Byte;

    template <typename T>
    using Group = std::vector<T>;

} // the end of namespace pg

#endif