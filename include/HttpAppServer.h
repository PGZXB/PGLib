#ifndef __HTTPAPPSERVER_H__
#define __HTTPAPPSERVER_H__

#include <HttpServer.h>
#include <HttpApplication.h>

#include <PGDef.h>

namespace pg {

    class HttpAppServer : public HttpServer {
    public:
        HttpAppServer(short p, const char * _ip = nullptr);
        virtual ~HttpAppServer();

        HttpAppServer & addApplicationBatch(const type::Group<HttpApplication *>  & batch);

        HttpAppServer & addApplication(HttpApplication * app);

        HttpAppServer & delApplication(HttpApplication * app);

    private:
        void response(const HttpRequest & __request, HttpResponse & __response) override;

    private:
        std::map<std::string, HttpApplication*> httpApps;
    };
} // namespace pg

#endif // !__HTTPAPPSERVER_H__
