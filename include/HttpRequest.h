#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include <map>
#include <string>
#include <vector>
#include <string.h>

#include <utils.h>


namespace pg {

    class HttpRequest {
        enum RequestMethod {
            GET,
            POST
        };
    public:
        explicit HttpRequest(const char * msg, char * contBuf = nullptr);

        explicit HttpRequest(std::string && requestMsg, char * contBuf = nullptr);
        explicit HttpRequest(const std::string &, char * contBuf = nullptr);

        virtual ~HttpRequest();

        const std::string & getUrl() const;

        const std::string & getValue(const std::string & key) const;

        const std::vector<std::string> & getValues(const std::string & key) const;
    
    protected:
        void init(const char * msg);

        void parseRequestLine(const char * header, char * method, char * content, char * httpVer);

        void parseArgs(const char * argsMsg);

        const char * skipToContent(const char * msg);
    
    protected:
        RequestMethod requestMethod;
        std::string url;
        std::map<std::string, std::vector<std::string>> requestArgs;
        std::vector<std::string> headerLines;
        std::string httpVertion;
        char * contentBuf = nullptr;  // used to save content
    };
    
} // the end of namespace pg


#endif