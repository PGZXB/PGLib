#ifndef __HTTPFILERESPONSEAPPLICATION_H__
#define __HTTPFILERESPONSEAPPLICATION_H__

#include <string>
#include <HttpApplication.h>

namespace pg {
    class HttpApplication;
    class HttpRequest;
    class HttpResponse;

    class HttpFileResponseApplication : public HttpApplication {
    public:
        HttpFileResponseApplication(const char * filename);
        virtual ~HttpFileResponseApplication();

        void exec(const HttpRequest &, HttpResponse &) override;
    
    protected:
        std::string filename;
        std::string contentType;
    };
} // namespace pg



#endif