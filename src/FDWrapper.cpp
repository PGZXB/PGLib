#include <base/FDWrapper.h>
#include <base/Buffer.h>

#include <unistd.h>

#include <iostream>

// FDWrapper's member functions
pg::base::FDWrapper::FDWrapper(int fd) : fd_(fd) { }
pg::base::FDWrapper::~FDWrapper() { if (fd_ != -1) ::close(fd_); }

void pg::base::FDWrapper::close() { if (fd_ != -1) ::close(fd_); }
const int pg::base::FDWrapper::data() { return fd_; }

ssize_t pg::base::FDWrapper::write(const Buffer & src, size_t len) {
    if (len == 0) len = src.size();

    return ::write(fd_, src.get(), len);
}

ssize_t pg::base::FDWrapper::readAll(Buffer & buf) const {
    char __buf[BUFSIZ] = { 0 };

    size_t __len = 0, __sum = 0;
    while ((__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
        __sum += __len;
        buf.push_back(__buf, __len);
    }
    return __sum;
}

std::string pg::base::FDWrapper::readAllAsString() const {
    char __buf[BUFSIZ] = { 0 };

    std::string res;

    std::size_t __len = 0, __sum = 0;
    while ((__len = ::read(fd_, __buf, BUFSIZ)) > 0) {
        __sum += __len;
        
        res.append(__buf, __len);
    }
    return res;
}

ssize_t pg::base::FDWrapper::read(Buffer & buf, size_t maxLen) const {
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

std::string pg::base::FDWrapper::readAsString(size_t maxLen) const {
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

// fd-about util-functions
int pg::base::getFd(const std::string & filename, pg::base::FileOpenMode::Mode mode) {
            
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
    else if (mode & FileOpenMode::Read)
        flags = O_RDONLY;
    
    return ::open(filename.c_str(), flags);
}