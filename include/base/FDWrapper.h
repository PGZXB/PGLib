#ifndef __FDWRAPPER_H__
#define __FDWRAPPER_H__

#include <cstdint>
#include <string>

namespace pg::base {
    using Buffer = class DynamicBuffer;  // BufferFWD

    class FDWrapper {
    public:
        FDWrapper(int fd);
        ~FDWrapper();

        FDWrapper(const FDWrapper &) = delete;
        FDWrapper(FDWrapper &&) = delete;

        FDWrapper & operator = (const FDWrapper &) = delete;
        FDWrapper & operator = (FDWrapper &&) = delete;

        void close();
        const int data();

        ssize_t write(const Buffer & src, size_t len = 0);

        ssize_t readAll(Buffer & buf) const;
        std::string readAllAsString() const ;

        ssize_t read(Buffer & buf, size_t maxLen) const;
        std::string readAsString(size_t maxLen) const;
    private:
        int fd_  = -1;
    };    
} // namespace pg::base


#endif