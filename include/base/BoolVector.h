#ifndef __BOOLVECTOR_H__
#define __BOOLVECTOR_H__

#include <vector>
#include <cstdint>

namespace pg::base {

    class BoolVector {
        using Int32 = std::int32_t ;
    public:
        BoolVector() {
            bVec_.push_back(0);
        }

        std::size_t size() { return size_; }

        void push_back(bool val) {
            if (size_ == BLOCK_SIZE * bVec_.size() ) bVec_.push_back(0);
            size_t offset = size_ % BLOCK_SIZE;
            bVec_.back() |= val << offset;
            ++size_;
        }

        bool operator[] (std::size_t idx) {
            if (idx >= size_) return false;

            size_t offset = ( (idx) % BLOCK_SIZE );
            return ( bVec_.at( (idx) / BLOCK_SIZE ) & (1 << offset) ) >> offset;
        }

    private:
        enum { BLOCK_SIZE = 32 };
        std::vector<Int32> bVec_;
        std::size_t size_ = 0;
    };
    
} // namespace pg::base


#endif