#ifndef __HTTPAPPSERVER_H__
#define __HTTPAPPSERVER_H__

#include <HttpServer.h>
#include <HttpApplication.h>

namespace pg {

    class HttpAppServer : public HttpServer {
    public:
        HttpAppServer(short p, const char * _ip = nullptr) : HttpServer(p, _ip) { }
        virtual ~HttpAppServer() = default;

        HttpAppServer & addApplication(HttpApplication * app) {
            httpApps[app->getUrl()] = app;

            return *this;
        }

        HttpAppServer & delApplication(HttpApplication * app) {
            std::map<std::string, HttpApplication*>::iterator iter = httpApps.find(app->getUrl());

            if (iter != httpApps.end()) httpApps.erase(iter);

            return *this;
        }

    private:
        void response(const HttpRequest & __request, HttpResponse & __response) override {
            std::map<std::string, HttpApplication*>::iterator iter = httpApps.find(__request.getUrl());

            if (iter != httpApps.end()) iter->second->exec(__request, __response);
        }

    private:
        std::map<std::string, HttpApplication*> httpApps;
    };
} // namespace pg

#endif // !__HTTPAPPSERVER_H__
