#include <HttpServer.h>

pg::HttpServer::HttpServer(short p, const char * _ip) : EpollTcpServer(p, _ip) {

}

pg::HttpServer::~HttpServer() {

}

void pg::HttpServer::response(const HttpRequest & __request, HttpResponse & __response) { 
}

void pg::HttpServer::process() {
    // parse the request-string to the HttpRequest-Object
    HttpRequest __request(this->getRecvMsg());
    // init a HttpResponse-Object to save the message to response to browser
    currResponse = new HttpResponse(this->getSendBuf(), this->getSendBufSize());

    // set response-data
    response(__request, *currResponse);
}

size_t pg::HttpServer::fillSendBuffer() {
    if (!headerFlushed) {
        headerFlushed = true;
        return currResponse->flushHeader();
    }

    if (currResponse->hasRem()) {
        return currResponse->flush();
    } else {
        delete currResponse;
        currResponse = nullptr;
        headerFlushed = false;
        return 0;
    }
}