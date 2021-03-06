#include <HttpFileResponseApplication.h>
#include <HttpApplication.h>
#include <HttpRequest.h>
#include <HttpResponse.h>

// public-functions
pg::HttpFileResponseApplication::HttpFileResponseApplication(const char * fileName) : pg::HttpApplication(), filename(fileName) {
    this->url = filename.substr(filename.find_last_of('/'));

    // printf("-----> %s\n", url.c_str());

    initContentType();

    // printf("-----> %s\n", contentType.c_str());
}

pg::HttpFileResponseApplication::HttpFileResponseApplication(const char * url_, const char * fileName) :  pg::HttpApplication(url_), filename(fileName) {
    // printf("-----> %s\n", url.c_str());

    initContentType();

    // printf("-----> %s\n", contentType.c_str());
}

pg::HttpFileResponseApplication::~HttpFileResponseApplication() {  }

void pg::HttpFileResponseApplication::setFileName(const char * fileName) {
    filename.assign(fileName);

    initContentType();
}

void pg::HttpFileResponseApplication::setFileName(const std::string & fileName) {
    filename.assign(fileName);

    initContentType();
}

void pg::HttpFileResponseApplication::setFileName(std::string && fileName) {
    filename.assign(fileName);

    initContentType();
}

void pg::HttpFileResponseApplication::exec(const HttpRequest & request, HttpResponse & response) {
    response.setContentType(contentType);
    response.setStatusCode(util::HTTP_SUCCESS_STATUS_CODE);
    response.pushFile_back(filename.c_str());
}

//private-functions
void pg::HttpFileResponseApplication::initContentType() {

    std::string suffixName = filename.substr(filename.find_last_of('.'));
    auto iter = util::HTTP_TYPENAME_OF_FSUFFIX.find(suffixName);
    this->contentType = iter == util::HTTP_TYPENAME_OF_FSUFFIX.end() ?
                            util::HTTP_DEFAULT_CONTENT_TYPE : iter->second;
  
}