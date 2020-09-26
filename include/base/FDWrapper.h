#ifndef __FDWRAPPER_H__
#define __FDWRAPPER_H__

#include <Buffer.h>

#include <unistd.h>
#include <cstdint>
namespace pg::base {
    class FDWrapper {
    public:
        FDWrapper(int fd) : fd_(fd) { }
        ~FDWrapper() { if (fd_ != -1) ::close(fd_); }

        void close() { if (fd_ != -1) ::close(fd_); }

        ssize_t write(const Buffer & src, size_t len = 0) {
            if (len == 0) len = src.size();

            return ::write(fd_, src.get(), len);
        }

        ssize_t readAll(Buffer & buf) const {
            char __buf[BUFSIZ] = { 0 };

            size_t __len = 0, __sum = 0;
            while ((__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
                __sum += __len;
                buf.push_back(__buf, __len);
            }
            return __sum;
        }

        std::string readAllAsString() const {
            char __buf[BUFSIZ] = { 0 };
            std::string res;

            size_t __len = 0, __sum = 0;
            while ((__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
                __sum += __len;
                res.append(__buf, __len);
            }
            return res;
        }

        ssize_t read(Buffer & buf, size_t maxLen) const {
            char __buf[BUFSIZ] = { 0 };

            size_t __len = 0, __sum = 0;
            __sum += ( __len = ::read(fd_, __buf, maxLen % BUFSIZ) );
            maxLen -= __len;
            buf.push_back(__buf, __len);
            while (maxLen > 0 && (__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
                __sum += __len;
                maxLen -= __len;
                buf.push_back(__buf, __len);
            }
            return __sum;
        }

        std::string readAsString(size_t maxLen) const {
            char __buf[BUFSIZ] = { 0 };
            std::string res;

            size_t __len = 0, __sum = 0;
            __sum += ( __len = ::read(fd_, __buf, maxLen % BUFSIZ) );
            maxLen -= __len;
            res.append(__buf, __len);
            while (maxLen > 0 && (__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
                __sum += __len;
                maxLen -= __len;
                res.append(__buf, __len);
            }
            return res;
        }
    private:
        int fd_  = -1;
    };    
} // namespace pg::base


#endif