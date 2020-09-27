#ifndef __FILEWRAPPER_H__
#define __FILEWRAPPER_H__

#include <cstdio>
#include <string>
#include <memory>

#include <base/pgfwd.h>

namespace pg::base {
    using Buffer = class DynamicBuffer;  // BufferFWD

    class FILEWrapper {
    public:
        FILEWrapper(std::FILE * pFILE = nullptr);
        ~FILEWrapper();

        FILEWrapper(const FILEWrapper &) = delete;
        FILEWrapper(FILEWrapper &&) = delete;

        FILEWrapper & operator = (const FILEWrapper &) = delete;
        FILEWrapper & operator = (FILEWrapper &&) = delete;

        void close();
        FILE * data();

        ssize_t write(const Buffer & src, size_t len = 0);

        ssize_t readAll(Buffer & buf) const;
        std::string readAllAsString() const;

        ssize_t read(Buffer & buf, size_t maxLen) const;
        std::string readAsString(size_t maxLen) const;

        static std::shared_ptr<FILEWrapper> getInstance(const std::string & filename, pg::base::FileOpenMode::Mode mode);
    private:
        std::FILE * pFILE_ = nullptr;
    };
    
} // namespace pg::base


#endif