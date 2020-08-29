#include <HttpAppServer.h>

pg::HttpAppServer::HttpAppServer(short p, const char * _ip) : HttpServer(p, _ip) { }

pg::HttpAppServer::~HttpAppServer() { }

pg::HttpAppServer & pg::HttpAppServer::addApplicationBatch(const type::Group<HttpApplication *>  & batch) {

    for (HttpApplication * e : batch) {
        httpApps[e->getUrl()] = e;
    }

    return *this;
}

pg::HttpAppServer & pg::HttpAppServer::addApplication(pg::HttpApplication * app) {
    httpApps[app->getUrl()] = app;

    return *this;
}

pg::HttpAppServer & pg::HttpAppServer::delApplication(pg::HttpApplication * app) {
    std::map<std::string, pg::HttpApplication*>::iterator iter = httpApps.find(app->getUrl());

    if (iter != httpApps.end()) httpApps.erase(iter);

    return *this;
}

void pg::HttpAppServer::response(const HttpRequest & __request, HttpResponse & __response) {
    std::map<std::string, HttpApplication*>::iterator iter = httpApps.find(__request.getUrl());

    if (iter != httpApps.end()) iter->second->exec(__request, __response);
}