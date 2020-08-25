#include <TcpServer.h>
#include <HttpServer.h>

int main() {

    pg::HttpServer(8080).run();

    return 0;
}