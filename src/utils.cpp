#include <utils.h>

#include <string.h>

const char * pg::util::CRLF = "\r\n";
const char * pg::util::LF = "\n";
const char * pg::util::CR = "\r";

const char * pg::util::getline(char * buf, const char * str, const char * flag) {
    const char * end = strstr(str, flag);
    if (end == NULL) return end;

    strncpy(buf, str, end - str);

    return end;
}