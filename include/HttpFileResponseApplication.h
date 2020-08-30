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
        explicit HttpFileResponseApplication(const char * filename);
        HttpFileResponseApplication(const char * url, const char * filename);
        virtual ~HttpFileResponseApplication();
        
        void setFileName(const char * fileName);
        void setFileName(const std::string & fileName);
        void setFileName(std::string && fileName);

        void exec(const HttpRequest &, HttpResponse &) override;
    
    private:
        void initContentType();

    protected:
        std::string filename;
        std::string contentType;
    };
} // namespace pg



#endif