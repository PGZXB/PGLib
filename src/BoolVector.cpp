#include <base/BoolVector.h>

pg::base::BoolVector::BoolVector() {
    bVec_.push_back(0);
}

std::size_t pg::base::BoolVector::size() { return size_; }

void pg::base::BoolVector::push_back(bool val) {
    if (size_ >= BLOCK_SIZE * bVec_.size() ) bVec_.push_back(0);
    size_t offset = size_ % BLOCK_SIZE;
    bVec_.back() |= val << offset;
    ++size_;
}

bool pg::base::BoolVector::operator[] (std::size_t idx) {
    if (idx >= size_) return false;

    size_t offset = ( (idx) % BLOCK_SIZE );
    return ( bVec_.at( (idx) / BLOCK_SIZE ) & (1 << offset) ) >> offset;
}
