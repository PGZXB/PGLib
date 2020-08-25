#ifndef __UTILS_H__
#define __UTILS_H__

#include <unordered_map>

namespace pg {
    namespace util {
        
        extern const char * CRLF;
        extern const char * LF;
        extern const char * CR;
        extern const char * EMPTY_STR;

        extern const std::unordered_map<int, std::string> STATUS_NAME_OF_CODE;

        const char * getline(char * buf, const char * str, const char * flag = CRLF);
    } // namespace util
} // namespace pg


#endif