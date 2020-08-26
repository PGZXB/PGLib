#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include <string>
#include <string.h>
#include <map>
#include <algorithm>

#include <utils.h>

#define RESPONSE_LINE_FMT "HTTP/1.1 %d %s\r\n"
#define RESPONSE_HEAD_FMT "%s: %s\r\n"
#define RESPONSE_CONTENT_FMT "%s"

namespace pg {
    
    class HttpResponse {
    public:
        HttpResponse(char * buf = nullptr, size_t bufsize = BUFSIZ) : buffer(buf), bufSize(bufsize) {
            if (buf == nullptr) buffer = new char[BUFSIZ];
        }
    
        virtual ~HttpResponse() { if (newBuffer) delete buffer; }

        void setStatusCode(int code) {
            this->statCode = code;
        }

        HttpResponse & setHeader(const std::string & key, const std::string & value) {
            responseHeader[key] = value;

            return *this;
        }

        void setContentType(const char * type) {
            setContentType(std::string(type));
        }

        void setContentType(const std::string & type) {
            responseHeader["Content-Type"] = type;
        }

        void setContentType(std::string && type) {
            responseHeader["Content-Type"] = std::string(type);
        }

        HttpResponse & push_back(const std::string & msg, const char * end = util::EMPTY_STR) { 
            responseBody.append(msg).append(end);

            return *this;
        }

        HttpResponse & push_back(const char * msg, int maxLen = -1, const char * end = util::EMPTY_STR) { 
            if (maxLen == -1) responseBody.append(msg).append(end);
            else responseBody.append(msg, maxLen).append(end);

            remContLen = responseBody.size();
            return *this;
        }

        const char * getBuffer() const { return buffer; }

        void clearBuffer() { memset(buffer, 0, strlen(buffer)); }

        bool hasRem() { return remContLen > 1; }

        int flush() {
            size_t __len = std::min(remContLen, bufSize);

            memset(buffer, 0, bufSize);
            memcpy(buffer, responseBody.c_str() + (responseBody.size() - remContLen), __len);
            
            remContLen -= __len;

            printf("#");
            if (!hasRem()) printf("\n");

            return __len;
        }

        int flushHeader(long int contLen = -1) {

            char buf[64] = { 0 };
            if (contLen == -1) sprintf(buf, "%ld", responseBody.size());
            else sprintf(buf, "%ld", contLen);

            responseHeader["Content-Length"] = std::string(buf);
            
            sprintf(buffer, RESPONSE_LINE_FMT, statCode, pg::util::HTTP_STATUS_NAME_OF_CODE.at(statCode).c_str());
            for (const std::pair<std::string, std::string> & e : responseHeader) {
                // KEY: VALUE
                sprintf(buffer + strlen(buffer), RESPONSE_HEAD_FMT, e.first.c_str(), e.second.c_str());
            }
            sprintf(buffer + strlen(buffer), "%s", util::CRLF);

            printf("Debug----->>>>  Line + Header {{\n%s\n}}\n", buffer);

            return strlen(buffer);
        }

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


#undef RESPONSE_LINE_FMT
#undef RESPONSE_HEAD_FMT
#undef RESPONSE_CONTENT_FMT

#endif