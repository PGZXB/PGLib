#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include <HttpRequest.h>
#include <HttpResponse.h>
#include <EpollTcpServer.h>

#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>

#include <string>

namespace pg {
    
    class HttpServer : public EpollTcpServer {
    public:
        HttpServer(short p, const char * _ip = nullptr);
        virtual ~HttpServer();
    
    protected:
        virtual void response(const HttpRequest & __request, HttpResponse & __response);

    private:
        void process() override;
        size_t fillSendBuffer() override;
        HttpResponse * currResponse = nullptr;
        bool headerFlushed = false;
    };
} // the end of namespace pg

#endif