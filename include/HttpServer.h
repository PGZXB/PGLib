#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include <TcpServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>

#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>

#include <string>

namespace pg {
    
    class HttpServer : public TcpServer {
    public:
        HttpServer(short p, const char * _ip = nullptr);
        virtual ~HttpServer();
    
    protected:
        virtual void response(const HttpRequest & __request, HttpResponse & __response);

    private:
        void process(bufferevent *bev) override;
        
    };
} // the end of namespace pg

#endif