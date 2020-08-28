#include <HttpResponse.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <stdint.h>
#include <string.h>
#include <string>
#include <map>

#define RESPONSE_LINE_FMT "HTTP/1.1 %d %s\r\n"
#define RESPONSE_HEAD_FMT "%s: %s\r\n"
#define RESPONSE_CONTENT_FMT "%s"

// public
pg::HttpResponse::HttpResponse(char * buf, size_t bufsize) : buffer(buf), bufSize(bufsize) {
    if (buf == nullptr) {
        buffer = new char[BUFSIZ];
        newBuffer = true;
    }
}

pg::HttpResponse::~HttpResponse() {

    if (newBuffer) delete buffer;
}


void pg::HttpResponse::setStatusCode(int code) {
    this->statCode = code;
}

pg::HttpResponse & pg::HttpResponse::setHeader(const std::string & key, const std::string & value) {
    responseHeader[key] = value;

    return *this;
}

void pg::HttpResponse::setContentType(const char * type) {
    setContentType(std::string(type));
}

void pg::HttpResponse::setContentType(const std::string & type) {
    responseHeader["Content-Type"] = type;
}

void pg::HttpResponse::setContentType(std::string && type) {
    responseHeader["Content-Type"] = type;
}

pg::HttpResponse & pg::HttpResponse::pushFile_back(const char * filename, const char * end) {
    int fd = ::open(filename, O_RDONLY);

    push_back(fd, end);

    ::close(fd);

    return *this;
}

pg::HttpResponse & pg::HttpResponse::push_back(int fd, const char * end) {
    char buf[BUFSIZ] = { 0 };
    int __len = 0;

    while ( (__len = ::read(fd, buf, sizeof(buf))) > 0 ) {
        push_back(buf, __len);
    }
    responseBody.append(end);

    return *this;
}

pg::HttpResponse & pg::HttpResponse::push_back(const std::string & msg, const char * end) { 
    responseBody.append(msg).append(end);

    return *this;
}

pg::HttpResponse & pg::HttpResponse::push_back(const char * msg, std::size_t maxLen, const char * end) { 
    if (maxLen == static_cast<size_t>(-1)) responseBody.append(msg).append(end);
    else responseBody.append(msg, maxLen).append(end);

    remContLen = responseBody.size();
    return *this;
}

const char * pg::HttpResponse::getBuffer() const { return buffer; }

void pg::HttpResponse::clearBuffer() { memset(buffer, 0, strlen(buffer)); }

bool pg::HttpResponse::hasRem() const { return remContLen > 1; }

int pg::HttpResponse::flush() {
    size_t __len = std::min(remContLen, bufSize);

    memset(buffer, 0, bufSize);
    memcpy(buffer, responseBody.c_str() + (responseBody.size() - remContLen), __len);
    
    remContLen -= __len;

    printf("#");
    if (!hasRem()) printf("\n");

    return __len;
}

int pg::HttpResponse::flushHeader(long int contLen) {

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

#undef RESPONSE_LINE_FMT
#undef RESPONSE_HEAD_FMT
#undef RESPONSE_CONTENT_FMT