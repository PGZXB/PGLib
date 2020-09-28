#include <base/FILEWrapper.h>
#include <base/Buffer.h>

pg::base::FILEWrapper::FILEWrapper(std::FILE * pFILE) : pFILE_(pFILE) { }
pg::base::FILEWrapper::~FILEWrapper() { close(); }

void pg::base::FILEWrapper::close() {
    if (pFILE_ != nullptr) std::fclose(pFILE_);
    pFILE_ = nullptr;
}
FILE * pg::base::FILEWrapper::data() { return pFILE_; }

ssize_t pg::base::FILEWrapper::write(const Buffer & src, size_t len) {
    if (len == 0) len = src.size();

    return std::fwrite(src.get(), 1, len, pFILE_);
}

ssize_t pg::base::FILEWrapper::readAll(Buffer & buf) const {
    char __buf[BUFSIZ] = { 0 };

    size_t __len = 0, __sum = 0;

    while ((__len = std::fread(__buf, 1, BUFSIZ, pFILE_)) > 0) {
        __sum += __len;
        buf.push_back(__buf, __len);
    }
    return __sum;
}
std::string pg::base::FILEWrapper::readAllAsString() const {
    char __buf[BUFSIZ] = { 0 };
    std::string res;

    size_t __len = 0, __sum = 0;
    while ((__len = std::fread(__buf, 1, BUFSIZ, pFILE_)) > 0) {
        __sum += __len;
        res.append(__buf, BUFSIZ);
    }
    return res;
}

ssize_t pg::base::FILEWrapper::read(Buffer & buf, size_t maxLen) const {
    char __buf[BUFSIZ] = { 0 };

    size_t __len = 0, __sum = 0;
    __sum += ( __len = std::fread(__buf, 1, maxLen % BUFSIZ, pFILE_) );
    maxLen -= __len;
    buf.push_back(__buf, __len);
    while (maxLen > 0 && (__len = std::fread(__buf, 1, BUFSIZ, pFILE_)) > 0) {
        __sum += __len;
        maxLen -= __len;
        buf.push_back(__buf, __len);
    }
    return __sum;
}
std::string pg::base::FILEWrapper::readAsString(size_t maxLen) const {
    char __buf[BUFSIZ] = { 0 };
    std::string res;

    size_t __len = 0, __sum = 0;
    __sum += ( __len = std::fread(__buf, 1, maxLen % BUFSIZ, pFILE_) );
    maxLen -= __len;
    res.append(__buf, __len);
    while (maxLen > 0 && (__len = std::fread(__buf, 1, BUFSIZ, pFILE_)) > 0) {
        __sum += __len;
        maxLen -= __len;
        res.append(__buf, __len);
    }
    return res;
}

// FILE-about util-functions
FILE * pg::base::getPFILE(const std::string & filename, pg::base::FileOpenMode::Mode mode) {
    using pg::base::FileOpenMode;
    std::string modeStr;

    if (mode & FileOpenMode::Write) {
        modeStr.push_back('w');
        if (mode & FileOpenMode::Read) modeStr.push_back('+');
    }
    else if (mode & FileOpenMode::Append) {
        modeStr.push_back('a');
        if (mode & FileOpenMode::Read) modeStr.push_back('+');
    }
    else if (mode & FileOpenMode::Read)
        modeStr.push_back('r');
    
    if (mode & FileOpenMode::Binary) modeStr.push_back('b');

    return std::fopen(filename.c_str(), modeStr.c_str());
}
