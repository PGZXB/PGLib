#ifndef __FILE_H__
#define __FILE_H__

#define private public
#define protected public

#include <base/FDWrapper.h>
#include <memory>

#include <base/pgfwd.h>

namespace pg::base {

    template <typename _FWrapper>  // FDWrapper & FILEWrapper
    class File : public _FWrapper {  // linux-based file
    private:
        using FileBaseWrapper = _FWrapper;
        std::shared_ptr<FileBaseWrapper> pFWrapper;
    public:
        File(std::string filename, FileOpenMode::Mode mode) {
            this->setData(FileBaseWrapper::getInstance(filename, mode));
        }

        ~File() {  }

    };
} // namespace pg::base

#endif