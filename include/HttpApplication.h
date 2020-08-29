#ifndef __HTTPAPPLICATION_H__
#define __HTTPAPPLICATION_H__

#include <HttpRequest.h>
#include <HttpResponse.h>

namespace pg {

    class HttpApplication {
    public:
        HttpApplication(const char * url = nullptr);
        virtual ~HttpApplication() = default;
        
        const std::string & getUrl() const;
        
        void setUrl(const char * url);
        void setUrl(const std::string & url);
        void setUrl(std::string && url);

        virtual void exec(const HttpRequest &, HttpResponse &) = 0;

    protected:
        std::string url = "/";
    };

} // namespace pg


#endif