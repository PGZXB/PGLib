#ifndef __BOOLVECTOR_H__
#define __BOOLVECTOR_H__

#include <vector>
#include <cstdint>

namespace pg::base {

    class BoolVector {
        using Int = std::int32_t;
    public:
        BoolVector();

        std::size_t size();

        void push_back(bool val);

        bool operator[] (std::size_t idx);

    private:
        enum { BLOCK_SIZE = sizeof(Int) * 8 };
        std::vector<Int> bVec_;
        std::size_t size_ = 0;
    };

} // namespace pg::base


#endif