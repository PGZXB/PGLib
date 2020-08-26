#ifndef __UTILS_H__
#define __UTILS_H__

#include <unordered_map>

namespace pg {
    namespace util {
        
        extern const char * CRLF;
        extern const char * LF;
        extern const char * CR;
        extern const char * EMPTY_STR;

        extern const int HTTP_SUCCESS_STATUS_CODE;
        extern const int HTTP_NOTFOUND_STATUS_CODE;

        extern const char * HTTP_CT_HTML;
        extern const char * HTTP_CT_PLAIN_TEXT;
        extern const char * HTTP_CT_XML;
        extern const char * HTTP_CT_GIF;
        extern const char * HTTP_CT_JPG;
        extern const char * HTTP_CT_PNG;
        extern const char * HTTP_CT_MP4;

        extern const std::unordered_map<int, std::string> HTTP_STATUS_NAME_OF_CODE;

        const char * getline(char * buf, const char * str, const char * flag = CRLF);
    } // namespace util
} // namespace pg


#endif