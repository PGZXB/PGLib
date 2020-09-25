#include <AutoHttpApplication.h>

pg::AutoHttpApplication::AutoHttpApplication(pg::AutoHttpApplication::ResponseFuncType respFunc, const char * url) 
    : pg::HttpApplication(url), responseFunction(respFunc) {

}

pg::AutoHttpApplication::AutoHttpApplication(const char * url) : HttpApplication(url) { 

}

pg::AutoHttpApplication::~AutoHttpApplication() = default;


void pg::AutoHttpApplication::exec(const HttpRequest & request, HttpResponse & response) {
    if (request.next()) {
        std::map<std::string, HttpApplication*>::iterator iter
                                                    = childAppMap.find(request.getUrl());

        if (iter != childAppMap.end()) iter->second->exec(request, response);
        else if (responseFunction && request.getUrl() == "/") responseFunction(request, response);
        else pg::Configure::getInstance()->get404Page()->exec(request, response); // 404

    } else if (responseFunction && request.getUrl() == "/") responseFunction(request, response);
    else pg::Configure::getInstance()->get404Page()->exec(request, response); // 404
}

void pg::AutoHttpApplication::pushChildApplication(pg::HttpApplication * childApp) {
    childAppMap[childApp->getUrl()] = childApp;
}

pg::HttpApplication * pg::AutoHttpApplication::getChildApplication(const std::string & url) {
    std::map<std::string, pg::HttpApplication*>::iterator iter = 
        childAppMap.find(url);
    if (iter != childAppMap.end()) return iter->second;
    return nullptr;
}
