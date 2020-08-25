#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <functional>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>

namespace pg {

    class TcpServer {
    public:
        TcpServer(short p, const char * _ip = nullptr);
        virtual ~TcpServer();

        int run();

    protected:
        virtual void process();

    protected:
        char ip[128] = { 0 };
        short port = 0;

        char sendBuf[BUFSIZ] = { 0 };
        ssize_t sendLen = 0;
        char recvBuf[BUFSIZ] = { 0 };
        ssize_t recvLen = 0;
    private:
        void listen(evconnlistener * listener, evutil_socket_t sock, sockaddr * addr, int socklen, void * arg);
        void read(bufferevent *bev, void *arg);
        void eventcb(bufferevent * bev, short what, void * arg);

        static void read_cb(bufferevent *bev, void *arg);
        static void listen_cb(evconnlistener * listener, evutil_socket_t sock, sockaddr * addr, int socklen, void * arg);
        static void event_cb(bufferevent * bev, short what, void * arg);

    private:
        event_base * base = nullptr;
        evconnlistener * listener = nullptr;
        sockaddr_in addr = { 0 };
    };

}  // the end of namespace pg
#endif