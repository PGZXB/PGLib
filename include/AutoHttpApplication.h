#ifndef __AUTOHTTPAPPLICATION_H__
#define __AUTOHTTPAPPLICATION_H__

#include <HttpApplication.h>

#include <map>
#include <functional>

namespace pg {
    
    class AutoHttpApplication : public HttpApplication {
        using ResponseFuncType = std::function<void(const HttpRequest &, HttpResponse &)>;
    public:
        AutoHttpApplication(ResponseFuncType respFunc, const char * url = nullptr) : HttpApplication(url), responseFunction(respFunc) { }
        AutoHttpApplication(const char * url = nullptr) : HttpApplication(url) { }
        ~AutoHttpApplication() = default;

        AutoHttpApplication(const AutoHttpApplication &) = delete;
        AutoHttpApplication(AutoHttpApplication &&) = delete;

        AutoHttpApplication & operator= (const AutoHttpApplication &) = delete;
        AutoHttpApplication & operator= (AutoHttpApplication &&) = delete;

        void exec(const HttpRequest & request, HttpResponse & response) override {
            if (request.next()) {
                std::map<std::string, HttpApplication*>::iterator iter 
                                                            = childAppMap.find(request.getUrl());

                if (iter != childAppMap.end()) iter->second->exec(request, response);
                else if (responseFunction) responseFunction(request, response);
                else pg::Configure::getInstance()->get404Page()->exec(request, response); // 404
            
            } else if (responseFunction) responseFunction(request, response);
            else pg::Configure::getInstance()->get404Page()->exec(request, response);; // 404
        }
    
        void pushChildApplication(HttpApplication * childApp) {
            childAppMap[childApp->getUrl()] = childApp;
        }

        HttpApplication * getChildApplication(const std::string & url) {
            std::map<std::string, HttpApplication*>::iterator iter = 
                childAppMap.find(url);
            if (iter != childAppMap.end()) return iter->second;
            return nullptr;
        }
    private:
        std::map<std::string, HttpApplication *> childAppMap;
        ResponseFuncType responseFunction;
    };
} // namespace pg
#endif