#ifndef __FDWRAPPER_H__
#define __FDWRAPPER_H__

#include <cstdint>
#include <string>

#include <sys/fcntl.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <memory>

#include <base/pgfwd.h>

namespace pg::base {
    using Buffer = class DynamicBuffer;  // BufferFWD

    class FDWrapper {
    public:
        FDWrapper() = default;
        FDWrapper(int fd);
        ~FDWrapper();

        FDWrapper(const FDWrapper &) = delete;
        FDWrapper(FDWrapper &&) = delete;

        void setData(int fd) {
            close();
            this->fd_ = fd; 
        }

        FDWrapper & operator = (const FDWrapper &) = delete;
        FDWrapper & operator = (FDWrapper &&) = delete;

        void close();
        const int data();

        ssize_t write(const Buffer & src, size_t len = 0);

        ssize_t readAll(Buffer & buf) const;
        std::string readAllAsString() const ;

        ssize_t read(Buffer & buf, size_t maxLen) const;
        std::string readAsString(size_t maxLen) const;

        static int getInstance(const std::string & filename, pg::base::FileOpenMode::Mode mode) {
            printf("%s %d||-----}}}\n", __FILE__, __LINE__);
            
            using pg::base::FileOpenMode;
            int flags = 0;

            if (mode & FileOpenMode::Write) {

                flags = O_WRONLY;
                if (mode & FileOpenMode::Read) flags |= O_RDONLY;
            }
            else if (mode & FileOpenMode::Append) {
                flags = O_APPEND;
                if (mode & FileOpenMode::Read) flags |= O_RDONLY;
            }
            else if (mode & FileOpenMode::Read) {
                printf("%s %d||-----@@@@@}}}\n", __FILE__, __LINE__);
                flags = O_RDONLY;
            }
            printf("||----- %d %d }}}\n", flags, O_RDONLY);

            // if (mode & FileOpenMode::Binary);
            int fd = ::open(filename.c_str(), flags);

            return fd;
        }
    private:
        int fd_  = -1;
    };    
} // namespace pg::base


#endif