#ifndef __PGDEF_H__
#define __PGDEF_H__

#include <vector>

namespace pg {
    namespace type {

        typedef char Byte;

        template <typename T>
        using Group = std::vector<T>;

    } // namespace type  
} // the end of namespace pg

#endif