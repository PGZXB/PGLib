#ifndef __DYNAMICARRAYWRAPPER_H__
#define __DYNAMICARRAYWRAPPER_H__

#include <utility>

namespace pg::tools {  // tools : helper-classes, util : helper-functions
    template <typename _Type>
    class DynamicArrayWrapper {
            using DataType = _Type;
            using DataPointerType = DataType*;
            using SizeType = std::size_t;
        public:
            DynamicArrayWrapper() { }
            DynamicArrayWrapper(DataPointerType array) : ptr(array) { }
            DynamicArrayWrapper(SizeType n) : ptr(new DataType[n]) { }

            void swap(DynamicArrayWrapper & other) noexcept {
                using std::swap;
                swap(other.ptr, ptr);
            }

            DataPointerType get() { return ptr; }

            ~DynamicArrayWrapper() { if (ptr != nullptr) delete [] ptr; }
        private:
            DataPointerType ptr = nullptr;
    };
} // namespace pg::tools

#endif