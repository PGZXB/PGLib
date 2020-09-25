#ifndef __DYNAMICARRAYWRAPPER_H__
#define __DYNAMICARRAYWRAPPER_H__

#include <utility>

namespace pg::base {  // tools : helper-classes, util : helper-functions
    template <typename _Type>
    class DynamicArrayWrapper {
            using DataType = _Type;
            using DataPointerType = DataType*;
            using SizeType = std::size_t;
        public:
            DynamicArrayWrapper() { }
            DynamicArrayWrapper(DataPointerType array) : ptr(array) { }
            explicit DynamicArrayWrapper(SizeType n) : ptr(new DataType[n]) { }

            DynamicArrayWrapper(const DynamicArrayWrapper &) = delete;
            DynamicArrayWrapper(DynamicArrayWrapper &&) = delete;

            DynamicArrayWrapper & operator= (const DynamicArrayWrapper &) = delete;
            DynamicArrayWrapper & operator= (DynamicArrayWrapper &&) = delete;

            void swap(DynamicArrayWrapper & other) noexcept {
                using std::swap;
                swap(other.ptr, ptr);
            }

            DataType & operator[] (SizeType idx) { return ptr[idx]; }

            DataPointerType get() { return ptr; }
            const DataType * get() const { return ptr; }

            ~DynamicArrayWrapper() { if (ptr != nullptr) delete [] ptr; }
            
            friend void swap(DynamicArrayWrapper & v1, DynamicArrayWrapper & v2) {
                v1.swap(v2);
            }
        private:
            DataPointerType ptr = nullptr;
    };
} // namespace pg::tools

#endif