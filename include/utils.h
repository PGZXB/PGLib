#ifndef __UTILS_H__
#define __UTILS_H__

#include <unordered_map>
#include <PGDef.h>

namespace pg {
    namespace util {
        
        extern const char * const CRLF;
        extern const char * const LF;
        extern const char * const CR;
        extern const char * const EMPTY_STR;

        extern const int HTTP_SUCCESS_STATUS_CODE;
        extern const int HTTP_NOTFOUND_STATUS_CODE;

        extern const char * const HTTP_CT_HTML;
        extern const char * const HTTP_CT_PLAIN_TEXT;
        extern const char * const HTTP_CT_XML;
        extern const char * const HTTP_CT_GIF;
        extern const char * const HTTP_CT_JPG;
        extern const char * const HTTP_CT_PNG;
        extern const char * const HTTP_CT_MP4;
        extern const char * const HTTP_CT_BIN;
        extern const char * const HTTP_CT_ICO;
        extern const char * const HTTP_DEFAULT_CONTENT_TYPE;


        extern const std::unordered_map<int, std::string> HTTP_STATUS_NAME_OF_CODE;
        extern const std::unordered_map<std::string, const char *> HTTP_TYPENAME_OF_FSUFFIX;

        extern const char * const CONFIG_FILE_NAME;

        namespace stringUtil {

            const char * getline(char * buf, const char * str, const char * flag = CRLF);
            
            pg::type::Group<std::string> split(const std::string & str, const char * splitFlag, int mode = 0);
            pg::type::Group<std::string> split(const std::string & str, const char ch, int mode = 0);

        } // namespace stringUtls
        
    } // namespace util

} // namespace pg


#endif