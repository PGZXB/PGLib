#include <HttpFileResponseApplication.h>
#include <HttpApplication.h>
#include <HttpRequest.h>
#include <HttpResponse.h>

pg::HttpFileResponseApplication::HttpFileResponseApplication(const char * fileName) : pg::HttpApplication(), filename(fileName) {
    url = filename.substr(filename.find_last_of('/'));

    // printf("-----> %s\n", url.c_str());

    std::string suffixName = filename.substr(filename.find_last_of('.'));
    auto iter = util::HTTP_TYPENAME_OF_FSUFFIX.find(suffixName);
    contentType = iter == util::HTTP_TYPENAME_OF_FSUFFIX.end() ? 
                                util::HTTP_DEFAULT_CONTENT_TYPE : iter->second;

    // printf("-----> %s\n", contentType.c_str());
}


pg::HttpFileResponseApplication::~HttpFileResponseApplication() {  }

void pg::HttpFileResponseApplication::exec(const HttpRequest & request, HttpResponse & response) {
    response.setContentType(contentType);
    response.setStatusCode(util::HTTP_SUCCESS_STATUS_CODE);
    response.pushFile_back(filename.c_str());
}