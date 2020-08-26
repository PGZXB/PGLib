#include <utils.h>

#include <string.h>
#include <utility>

const char * pg::util::CRLF = "\r\n";
const char * pg::util::LF = "\n";
const char * pg::util::CR = "\r";
const char * pg::util::EMPTY_STR = "";

const int pg::util::HTTP_SUCCESS_STATUS_CODE = 200;
const int pg::util::HTTP_NOTFOUND_STATUS_CODE = 404;

const char * pg::util::HTTP_CT_HTML = "text/html";
const char * pg::util::HTTP_CT_PLAIN_TEXT = "text/plain";
const char * pg::util::HTTP_CT_XML = "text/xml";
const char * pg::util::HTTP_CT_GIF = "image/gif";
const char * pg::util::HTTP_CT_JPG = "image/jpeg";
const char * pg::util::HTTP_CT_PNG = "image/png";
const char * pg::util::HTTP_CT_MP4 = "video/mpeg4";

/* status-code & name
 * 200("OK")
 * 400("Bad Request")
 * 500("Internal Server Error")
 * 301("Moved Permanently")
 * 404("Not Found") 和 410("Gone")
 * 409("Conflict")
 */
const std::unordered_map<int, std::string> pg::util::HTTP_STATUS_NAME_OF_CODE = {
    std::pair<int, std::string>(200, "OK"),
    std::pair<int, std::string>(400, "Bad Request"),
    std::pair<int, std::string>(500, "Internal Server Error"),
    std::pair<int, std::string>(301, "Moved Permanently"),
    std::pair<int, std::string>(404, "Not Found"),
    std::pair<int, std::string>(410, "Gone"),
    std::pair<int, std::string>(409, "Conflict")
};

const char * pg::util::getline(char * buf, const char * str, const char * flag) {
    const char * end = strstr(str, flag);
    if (end == NULL) return end;

    strncpy(buf, str, end - str);

    return end;
}