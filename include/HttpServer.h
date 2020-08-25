#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include <TcpServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>

#include <string>

namespace pg {
    
    // class HttpResponse;

    class HttpServer : public TcpServer {
    public:
        HttpServer(short p, const char * _ip = nullptr) : TcpServer(p, _ip) { }
        virtual ~HttpServer() = default;
    
    protected:
        virtual void response(const HttpRequest &, HttpResponse &) {  }

    private:
        void process() override {
            // parse the recvMsg to HttpRequest
            HttpRequest request(std::string(recvBuf, recvLen));
            // response(request, response);
            HttpResponse reponse(sendBuf);
// "HTTP/1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent-Length: %zu\r\nconnection:close\r\n\r\n%s", sizeof(buff) + 1, buff);
            reponse.setHeader("Content-Type", "text/html;charset=utf-8");
            reponse.push_back("<h1><font color=\"red\">")
                    .push_back(request.getValue("name"))
                    .push_back("</font></h1>");
            reponse.flush(200);
            sendLen = strlen(sendBuf);
            // put the msg of HttpResponse to the sendBuf
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
