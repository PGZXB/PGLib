#ifndef __EPOLLTCPSERVER_H__
#define __EPOLLTCPSERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <functional>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <errno.h>

#define FD_MAX_SIZE 1024

#define put_error(msg) {\
	fputs(msg "\n", stderr);\
}

namespace pg {

    class EpollTcpServer {
    public:
        EpollTcpServer(short p, const char * _ip = nullptr) : port(p) {
            if (_ip != nullptr) strcpy(this->ip, _ip);
            
            if ( (serverFd = ::socket(AF_INET, SOCK_STREAM, 0) ) ==  -1) put_error("Socket Error");

            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            if (_ip == nullptr)
                addr.sin_addr.s_addr =  htonl(INADDR_ANY);
            else
                addr.sin_addr.s_addr = inet_addr(this->ip);

            int opt = 1;
	        if (::setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt)) == -1) put_error("Set Opt Error");

            if (::bind(serverFd, (const sockaddr *)&addr, sizeof(sockaddr)) == -1) put_error("Bind Error");

            if (::listen(serverFd, 128) == -1) put_error("Listen Error");

            if ( ( epollFd = ::epoll_create(FD_MAX_SIZE) ) == -1) {
                put_error("epoll create error");
            }

            epoll_event temp;

            temp.events = EPOLLIN;
            temp.data.fd = serverFd;
            ::epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &temp);
        }

        virtual ~EpollTcpServer() {
            ::close(serverFd);
        }

        int run() {
            epoll_event temp;
            int activeNum = 0;
            sockaddr_in cliAddr;
	        int cliAddrLen = sizeof(sockaddr_in);
	        while (true) {
                printf("$$$$$\n");
                int fd = 0;
                activeNum = ::epoll_wait(epollFd, epollEvents, FD_MAX_SIZE, -1);
                if (activeNum == 0) continue;

                for (int i = 0; i < activeNum; ++i) {
                    printf("##### %d\n", i);
                    if ( !( epollEvents[i].events & EPOLLIN ) ) continue;
                    fd = epollEvents[i].data.fd;

                    if (fd == serverFd) {  // new client joins
                        int clientFd = 0;
                        clientFd = ::accept(serverFd, (sockaddr *)&cliAddr, (socklen_t*)&cliAddrLen);
                        if (clientFd == -1) put_error("Accept Error");

                        // add the new fd into the epoll_tree
                        temp.events = EPOLLIN;
                        temp.data.fd = clientFd;
                        ::epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &temp);

                        ::printf("New Client [IP : %s, PORT : %d]\n",
                            ::inet_ntoa(cliAddr.sin_addr) ,::ntohs(cliAddr.sin_port));
                    } else {  // other fds ---- the clients
                        // recv
                        char buf[BUFSIZ];
                        int recvLen = 0;
                        ::memset(buf, 0, sizeof(buf));
                        if ( ( recvLen = ::read(fd, buf, sizeof(buf)) ) <= 0 ) {
                            // reomve the fd from the epoll-tree
                            ::epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, nullptr);
                            // close the client
                            ::close(fd);

                            ::printf("A Client[%d] Diconnected From This Server\n", fd);	
                            continue;
                        } else {
                            recvBuffer.append(buf, recvLen);
                            if (recvLen == BUFSIZ) {
                                while (( recvLen = ::read(fd, buf, sizeof(buf)) ) > 0) {
                                    recvBuffer.append(buf, recvLen);
                                }
                            }
                        }
                        ::printf("Recv From Client[%d] : %s\n", fd, recvBuffer.c_str());

                        // process
                        process();
                        recvBuffer.clear();

                        // send
                        int sendLen = 0;
                        while ((sendLen = fillSendBuffer()) > 0) {
                            // std::puts(buf);
                            if ( ::write(fd, sendBuf, sendLen) < 0 ) put_error("Send Ivalid Data");
                        }
			        }

		        }

	        }
        
        }

        virtual size_t fillSendBuffer() = 0;
        virtual void process() = 0;
        
        size_t getSendBufSize() const {
            return BUFSIZ;
        }

        char * getSendBuf() {
            return sendBuf;
        }

        std::string & getRecvMsg() {
            return recvBuffer;
        }

    private:
        int serverFd = -1;
        int epollFd = 0;
        char ip[128] = { 0 };
        short port = 0;
        sockaddr_in addr = { 0 };
        epoll_event epollEvents[FD_MAX_SIZE];
        std::string recvBuffer;
        char sendBuf[BUFSIZ] = { 0 };
        size_t sendLen = 0;
    };
    
} // namespace pg
#endif