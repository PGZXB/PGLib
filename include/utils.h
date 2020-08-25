#ifndef __UTILS_H__
#define __UTILS_H__

namespace pg {
    namespace util {
        
        extern const char * CRLF;
        extern const char * LF;
        extern const char * CR;

        const char * getline(char * buf, const char * str, const char * flag = CRLF);
    } // namespace util
} // namespace pg


#endif