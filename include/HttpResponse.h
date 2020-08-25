#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include <string>
#include <string.h>
#include <map>

#include <utils.h>

#define RESPONSE_LINE_FMT "HTTP/1.1 %d %s\r\n"
#define RESPONSE_HEAD_FMT "%s: %s\r\n"
#define RESPONSE_CONTENT_FMT "%s"

namespace pg {
    
    class HttpResponse {
    public:
        HttpResponse(char * buf = nullptr) : buffer(buf) {
            if (buf == nullptr) buffer = new char[BUFSIZ];
        }
    
        virtual ~HttpResponse() { if (newBuffer) delete buffer; }

        HttpResponse & push_back(std::string msg, const char * end = util::EMPTY_STR) { 
            responseBody.append(msg).append(end);

            return *this;
        }

        HttpResponse & setHeader(const std::string & key, const std::string & value) {
            responseHeader[key] = value;

            return *this;
        }
        
        const char * getBuffer() { return buffer; }

        void clearBuffer() { memset(buffer, 0, strlen(buffer)); }

        const char * flush(int statusCode) {

            char buf[64] = { 0 };
            sprintf(buf, "%ld", responseBody.size());
            responseHeader["Content-Length"] = std::string(buf);
            
            sprintf(buffer, RESPONSE_LINE_FMT, statusCode, pg::util::STATUS_NAME_OF_CODE.at(statusCode).c_str());
            for (const std::pair<std::string, std::string> & e : responseHeader) {
                // KEY:VALUE
                sprintf(buffer + strlen(buffer), RESPONSE_HEAD_FMT, e.first.c_str(), e.second.c_str());
            }
            sprintf(buffer + strlen(buffer), "%s", util::CRLF);
            sprintf(buffer + strlen(buffer), "%s", responseBody.c_str());

            printf("Debug----->>>>   {{\n%s\n}}\n", buffer);

            return buffer;
        }

    protected:
        void init() {
            
        }

    protected:
        bool newBuffer  = false;

        char * buffer = nullptr;
        std::map<std::string, std::string> responseHeader;
        std::string responseBody;
    };


} // namespace pg


#undef RESPONSE_LINE_FMT
#undef RESPONSE_HEAD_FMT
#undef RESPONSE_CONTENT_FMT

#endif