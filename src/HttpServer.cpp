#include <HttpServer.h>

pg::HttpServer::HttpServer(short p, const char * _ip) : TcpServer(p, _ip) {

}

pg::HttpServer::~HttpServer() {

}

void pg::HttpServer::response(const HttpRequest & __request, HttpResponse & __response) { 
    // if (__request.getUrl() == "/") {

    //     __response.setContentType(util::HTTP_CT_HTML);
    //     __response.pushFile_back("/home/pgzxb/Pictures/home.html");
    // }else if (__request.getUrl() == "/movie.mp4") {

    //     __response.setContentType(util::HTTP_CT_MP4);
    //     __response.pushFile_back("/home/pgzxb/Pictures/test.mp4");
    // } else if (__request.getUrl() == "/movie") {

    //     __response.setContentType(util::HTTP_CT_HTML);
    //     __response.pushFile_back("/home/pgzxb/Pictures/test.html");
    // } else if (__request.getUrl() == "/favicon.ico") {

    //     __response.setContentType(util::HTTP_CT_JPG);
    //     __response.pushFile_back("/home/pgzxb/Pictures/test.jpg");
    // }

    // __response.setStatusCode(util::HTTP_SUCCESS_STATUS_CODE);
}

void pg::HttpServer::process(bufferevent *bev) {
    HttpRequest __request(std::string(recvBuf, recvLen));
    HttpResponse __response(sendBuf);

    response(__request, __response);

    this->sendLen = __response.flushHeader();
    writeTo(bev);
    while (__response.hasRem()) {
        this->sendLen = __response.flush();
        writeTo(bev);
    }
    this->sendLen = 0;
}