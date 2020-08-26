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
    
    // class HttpResponse;

    class HttpServer : public TcpServer {
    public:
        HttpServer(short p, const char * _ip = nullptr) : TcpServer(p, _ip) { }
        virtual ~HttpServer() = default;
    
    protected:
        virtual void response(const HttpRequest & __request, HttpResponse & __response) { 
            // __response.setContentType(util::HTTP_CT_PLAIN_TEXT);
            // __response.push_back("<h1><font color=\"red\">")
                    // .push_back(__request.getValue("name"))
                    // .push_back("</font></h1>");
            if (__request.getUrl() == "/movie.mp4") {
                __response.setContentType(util::HTTP_CT_MP4);
                int fd = ::open("/home/pgzxb/Pictures/test.mp4", O_RDONLY);
                ::fcntl(fd, O_NONBLOCK);
                char buf[BUFSIZ]; int len;
                while ( (len = ::read(fd, buf, sizeof(buf)) ) > 0) {
                    __response.push_back(buf, len);
                }
            } else if (__request.getUrl() == "/movie") {
                __response.setContentType(util::HTTP_CT_HTML);
                int fd = ::open("/home/pgzxb/Pictures/test.html", O_RDONLY);
                ::fcntl(fd, O_NONBLOCK);
                char buf[BUFSIZ]; int len;
                while ( (len = ::read(fd, buf, sizeof(buf)) ) > 0) {
                    __response.push_back(buf, len);
                }
            }

            __response.setStatusCode(util::HTTP_SUCCESS_STATUS_CODE);
         }

    private:
        void process(bufferevent *bev) override {
            HttpRequest __request(std::string(recvBuf, recvLen));
            HttpResponse __response(sendBuf);

            response(__request, __response);

            sendLen = __response.flushHeader();
            writeTo(bev);
            while (__response.hasRem()) {
                sendLen = __response.flush();
                writeTo(bev);
            }
            sendLen = 0;
        }
    };
} // the end of namespace pg


#endif




            // char buff[] = 
            //                 "<html>"
            //                 "<head>"
            //                 "<title>目录</title>"
            //                 "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />"
            //                 "</head>"
            //                 "<body>"
            //                 "<h1>目录</h1>"
            //                 "<ul>"
            //                 "<li><a href=\"集合论.html\">集合论</a></li>"
            //                 "<li><a href=\"二元关系.html\">二元关系</a></li>"
            //                 "<li><a href=\"关系的运算%26等价关系和划分(初步).html\">关系的运算&amp;等价关系和划分(初步)</a></li>"
            //                 "<li><a href=\"偏序关系.html\">偏序关系</a></li>"
            //                 "<li><a href=\"图论(1)-图的基本概念.html\">图论(1)-图的基本概念</a></li>"
            //                 "<li><a href=\"图论(2)-路径和回路.html\">图论(2)-路径和回路</a></li>"
            //                 "<li><a href=\"图论(3)-图的矩阵表示.html\">图论(3)-图的矩阵表示</a></li>"
            //                 "</ul>"
            //                 "</body>"
            //                 "</html>";
            // if (request.getUrl() == "/index") {
            // sprintf(sendBuf, "HTTP/1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent-Length: %zu\r\nconnection:close\r\n\r\n%s", sizeof(buff) + 1, buff);
            // printf("%s\n", sendBuf);
            // sendLen = strlen(sendBuf);
            // } else if (request.getUrl() == "/login") {
            //     char bufff[128];
            //     sprintf(bufff, "<h1> <font color=\"red\">name=%s age=%s</font></h1>", request.getValue("name").data(), request.getValue("age").data());
            //     printf("Debug------>>>>> %s,   %s", request.getValue("name").data(), request.getValue("age").data());
            //     sprintf(sendBuf, "HTTP/1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent-Length: %zu\r\nconnection:close\r\n\r\n%s", strlen(bufff) + 1, bufff);
            //     sendLen = strlen(sendBuf);
            // } else if (request.getUrl() == "/favicon.ico") {
            //     sprintf(sendBuf, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: 0\r\nconnection:close\r\n\r\n");
            //     sendLen = strlen(sendBuf);
            // }
