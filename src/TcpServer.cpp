#include <TcpServer.h>

// public-functions --------------------------------------------------------------------

pg::TcpServer::TcpServer(short p, const char * _ip) : port(p) {
    if (_ip != nullptr) strcpy(this->ip, _ip);
    // strcpy(this->ip, _ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (strlen(this->ip) == 0)
        addr.sin_addr.s_addr =  htonl(INADDR_ANY);
    else
        addr.sin_addr.s_addr = inet_addr(this->ip);
    
    base = event_base_new();
    listener = evconnlistener_new_bind(
        base, listen_cb, this, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1, (sockaddr *)&addr, sizeof(addr));    
}

int pg::TcpServer::run() {
    event_base_dispatch(base);

    return 0;
}

pg::TcpServer::~TcpServer() {
    evconnlistener_free(listener);
    event_base_free(base);
}

// ----------------------------------------------------------------------------------------

// protected-functions --------------------------------------------------------------------

void pg::TcpServer::process() {  // is a virtual function
    strcpy(sendBuf, recvBuf);  // echo-server
    sendLen = recvLen;
}

// ----------------------------------------------------------------------------------------


// private-functions ----------------------------------------------------------------------

void pg::TcpServer::listen(evconnlistener * listener, evutil_socket_t sock, sockaddr * addr, int socklen, void * arg) {
    sockaddr_in * addr_in = (sockaddr_in *)addr;

    printf("New Client[ %s : %d ]\n", inet_ntoa(addr_in->sin_addr), ntohs(addr_in->sin_port));

    bufferevent * ev =  bufferevent_socket_new(this->base, sock, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_enable(ev, EV_WRITE | EV_READ);
    bufferevent_setcb(ev, read_cb, NULL, event_cb, this);
}

void pg::TcpServer::read(bufferevent *bev, void *arg) {

    memset(recvBuf, 0, sizeof(recvBuf));
    recvLen = bufferevent_read(bev, recvBuf, sizeof(recvBuf));
    std::printf("Recv : {{\n\"%s\"\n}}\n", recvBuf);

    memset(sendBuf, 0, sizeof(sendBuf));
    process();

    bufferevent_write(bev, sendBuf, sendLen);
}

void pg::TcpServer::eventcb(bufferevent * bev, short what, void * arg) {
    if (what & BEV_EVENT_EOF) {
        std::printf("Diconnected");
        bufferevent_free(bev);
    } else if (what & BEV_EVENT_ERROR) {
        std::printf("Error");
        bufferevent_free(bev);
    }
}


// static-functions
void pg::TcpServer::read_cb(bufferevent *bev, void *arg) {
    TcpServer * server = (TcpServer *)arg;
    server->read(bev, NULL);        
}
void pg::TcpServer::listen_cb(evconnlistener * listener, evutil_socket_t sock, sockaddr * addr, int socklen, void * arg) {
    TcpServer * server = (TcpServer *)arg;
    server->listen(listener, sock, addr, socklen, NULL);    
}
void pg::TcpServer::event_cb(bufferevent * bev, short what, void * arg) {
    TcpServer * server = (TcpServer *)arg;

    server->eventcb(bev, what, NULL);
}

// ---------------------------------------------------------------------------------------------

