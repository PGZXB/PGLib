#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include <string>
#include <map>

#include <utils.h>

namespace pg {
    
    class HttpResponse {
    public:
        HttpResponse(char * buf = nullptr, size_t bufsize = BUFSIZ);
    
        virtual ~HttpResponse();

        void setStatusCode(int code);

        HttpResponse & setHeader(const std::string & key, const std::string & value);

        void setContentType(const char * type);
        void setContentType(const std::string & type);
        void setContentType(std::string && type);

        HttpResponse & pushFile_back(const char * filename, const char * end = util::EMPTY_STR);

        HttpResponse & push_back(int fd, const char * end = util::EMPTY_STR);
        HttpResponse & push_back(const std::string & msg, const char * end = util::EMPTY_STR);
        HttpResponse & push_back(const char * msg, std::size_t maxLen = -1, const char * end = util::EMPTY_STR);

        const char * getBuffer() const;

        bool hasRem() const;

        void clearBuffer();

        int flushHeader(long int contLen = -1);

        int flush();

    protected:
        bool newBuffer  = false;

        char * buffer = nullptr;
        size_t bufSize;
        size_t remContLen = 0;
        int statCode = util::HTTP_SUCCESS_STATUS_CODE;
        std::map<std::string, std::string> responseHeader;
        std::string responseBody;
    };


} // namespace pg

#endif