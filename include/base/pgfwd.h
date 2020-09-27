#ifndef __PGFWD_H__
#define __PGFWD_H__

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


#endif