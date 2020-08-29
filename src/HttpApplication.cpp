#include <HttpApplication.h>

pg::HttpApplication::HttpApplication(const char * requestUrl) {
    if (requestUrl != nullptr) url = requestUrl;
}

const std::string & pg::HttpApplication::getUrl() const {
    return url;
}

void pg::HttpApplication::setUrl(const char * url) {
    this->url.operator=(url);
}

void pg::HttpApplication::setUrl(const std::string & url) {
    this->url = url;
}

void pg::HttpApplication::setUrl(std::string && url) {
    this->url = url;
}