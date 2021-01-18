#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <vector>
#include <array>
#include <algorithm>
#include <cstring>
#include <stdio.h>

#include <PGDef.h>  // type::Byte
#include <base/DynamicArrayWrapper.h>

namespace pg::base {
    class DynamicBuffer;

    template <size_t size>
    class StaticBuffer;

    using Buffer = DynamicBuffer;

    // DynamicBuffer
    class DynamicBuffer {
        static const int DEFAULT_SIZE = 4096;
        using Byte = type::Byte;
        using ByteArray = base::DynamicArrayWrapper<Byte>;
    public:
        DynamicBuffer(size_t deftSize = DEFAULT_SIZE) : bBuf_(deftSize), cap_(deftSize) { }

        const Byte * get() const { return bBuf_.get(); }

        std::size_t size() const { return this->size_; }

        void clear() {
            std::memset(bBuf_.get(), 0, cap_);
            this->size_ = 0;
        }

        template <typename _Type>
        void push_back(const _Type & val) {
            this->push_back(&val, sizeof(_Type));
        }

        void push_back(const void * pVal, size_t siz) {

            size_t minLen = siz + this->size_;
            extend(minLen);
            std::memcpy(bBuf_.get() + this->size_, (void *)pVal, siz);
            this->size_ = minLen;
        }

        template <typename _Type>
        void append(const _Type & val) {
            this->push_back(&val, sizeof(_Type));
        }

    private:
        void extend(size_t minLen) {
            if (minLen <= cap_) return;

            ByteArray tmp(cap_ = minLen << 1);
            swap(bBuf_, tmp);
            std::memcpy(bBuf_.get(), tmp.get(), size_);
        }
        
    private:
        ByteArray bBuf_;
        std::size_t size_ = 0;
        std::size_t cap_ = 0;
    };

    // StaticBuffer
    template <std::size_t SIZE>
    class StaticBuffer {
        using Byte = type::Byte;
        using ByteArray = Byte[SIZE];
    public:
        StaticBuffer() = default;

        const Byte * get() const { return bBuf_; }
        std::size_t size() const { return this->size_; }

        void clear() {
            std::memset(bBuf_.get(), 0, SIZE);
            this->size_ = 0;
        }

        template <typename _Type>
        bool push_back(const _Type & val) {
            return this->push_back(&val, sizeof(_Type));
        }

        bool push_back(const void * pVal, size_t siz) {

            size_t minLen = siz + this->size_;
            if (minLen > SIZE) return false;
            std::memcpy(bBuf_ + this->size_, (void *)pVal, siz);
            this->size_ = minLen;

            return true;
        }

    private:
        ByteArray bBuf_ = { 0 };
        std::size_t size_ = 0;
    };
} // namespace pg::base




#endif