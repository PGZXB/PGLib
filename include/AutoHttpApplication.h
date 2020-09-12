#ifndef __AUTOHTTPAPPLICATION_H__
#define __AUTOHTTPAPPLICATION_H__

#include <HttpApplication.h>
#include <Configure.h>

#include <map>
#include <functional>

namespace pg {
    
    class AutoHttpApplication : public HttpApplication {
        using ResponseFuncType = std::function<void(const HttpRequest &, HttpResponse &)>;
    public:
        AutoHttpApplication(ResponseFuncType respFunc, const char * url = nullptr);
        AutoHttpApplication(const char * url = nullptr);
        ~AutoHttpApplication();

        AutoHttpApplication(const AutoHttpApplication &) = delete;
        AutoHttpApplication(AutoHttpApplication &&) = delete;

        AutoHttpApplication & operator= (const AutoHttpApplication &) = delete;
        AutoHttpApplication & operator= (AutoHttpApplication &&) = delete;

        void exec(const HttpRequest & request, HttpResponse & response);
    
        void pushChildApplication(HttpApplication * childApp);

        HttpApplication * getChildApplication(const std::string & url);
    private:
        std::map<std::string, HttpApplication*> childAppMap;
        ResponseFuncType responseFunction;
    };
} // namespace pg
#endif