#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <vector>
#include <algorithm>
#include <cstring>

#include <PGDef.h>  // type::Byte
#include <DynamicArrayWrapper.h>

namespace pg::base {
    class DynamicBuffer;

    using Buffer = DynamicBuffer;

    class DynamicBuffer {
        static const int DEFAULT_SIZE = 4096;
        using Byte = type::Byte;
        using ByteArray = base::DynamicArrayWrapper<Byte>;
    public:
        DynamicBuffer() : bBuf(DEFAULT_SIZE), cap(DEFAULT_SIZE) { }

        const Byte * get() const {
            return bBuf.get();
        }

        void clear() {
            std::memset(bBuf.get(), 0, cap);
        }

        template<typename _Type>
        void push_back(_Type val) {
            size_t len = sizeof(_Type);
            size_t minLen = size + len;
            if (minLen > cap) {
                ByteArray tmp(cap = minLen << 1);
                swap(bBuf, tmp);
                std::memcpy(bBuf.get(), tmp.get(), size);
            }
            std::memcpy(bBuf.get() + size, (void *)&val, len);
            size = minLen;
        }

    private:
        ByteArray bBuf;
        std::size_t size = 0;
        std::size_t cap = 0;
    };
} // namespace pg::base




#endif