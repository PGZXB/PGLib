#ifndef __PAGE_H__
#define __PAGE_H__

#include <memory>

#include <base/File.h>
#include <base/Buffer.h>
#include <fmt_util.h>

// PGLib.Page 1.0 : just format the src-html-file by the defined rules

namespace pg {
    
    class Page {
    public:
        Page() = default;

        explicit Page(const pg::base::File & srcFile)
            : _srcFile(new pg::base::File(srcFile.getAbsolutePath())) {
        }

        explicit Page(const std::string & srcFilePath)
            : _srcFile(new pg::base::File(srcFilePath)) {
        }

        ~Page() = default;

        void setSrcFile(const pg::base::File & srcFile) {
            _srcFile.reset(new pg::base::File(srcFile.getAbsolutePath()));
        }

        void setSrcFile(const std::string & srcFilePath) {
            _srcFile.reset(new pg::base::File(srcFilePath));
        }

        template <typename..._Args>
        std::string formatAll(_Args...args) {
            return pg::util::stringUtil::format(
                _srcFile->getFILEWrapper()->readAllAsString(), args...);
        }

        template <typename _Res, typename..._Args>
        void formatBatchTo(_Res & res) {  // Base-Tools is not 
            auto filePtr = _srcFile->getFILEWrapper();
            pg::base::Buffer buf;

            filePtr->read(buf, 1024);

            // pg::util::stringUtil::format(res, std::string(buf.get()), );
        }

        // void saveAsString(std::string & to) {
        // }

        // void saveAsString(char * to) {
        // }

        // void saveToBuffer(pg::base::DynamicBuffer & buffer) {
        // }

        // void saveAsFile(const std::string & filename) {
        // }

        
    private:
        std::shared_ptr<pg::base::File> _srcFile;
    };

} // namespace pg 


#endif  // !__PAGE_H__