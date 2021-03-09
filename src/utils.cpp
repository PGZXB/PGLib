#include <utils.h>
#include <PGDef.h>

#include <string.h>
#include <string>
#include <utility>
#include <vector>

const char * const pg::util::CONFIG_FILE_NAME = "../config.json";

const char * const pg::util::CRLF = "\r\n";
const char * const pg::util::LF = "\n";
const char * const pg::util::CR = "\r";
const char * const pg::util::EMPTY_STR = "";

const int pg::util::HTTP_SUCCESS_STATUS_CODE = 200;
const int pg::util::HTTP_NOTFOUND_STATUS_CODE = 404;

const char * const pg::util::HTTP_CT_HTML = "text/html";
const char * const pg::util::HTTP_CT_PLAIN_TEXT = "text/plain";
const char * const pg::util::HTTP_CT_XML = "text/xml";
const char * const pg::util::HTTP_CT_GIF = "image/gif";
const char * const pg::util::HTTP_CT_JPG = "image/jpeg";
const char * const pg::util::HTTP_CT_PNG = "image/png";
const char * const pg::util::HTTP_CT_MP4 = "video/mpeg4";
const char * const pg::util::HTTP_CT_BIN = "application/octet-stream";
const char * const pg::util::HTTP_CT_ICO = "image/x-icon";

const char * const pg::util::HTTP_DEFAULT_CONTENT_TYPE = pg::util::HTTP_CT_BIN;

const std::unordered_map<int, std::string> pg::util::HTTP_STATUS_NAME_OF_CODE = {
    std::pair<int, std::string>(200, "OK"),
    std::pair<int, std::string>(400, "Bad Request"),
    std::pair<int, std::string>(500, "Internal Server Error"),
    std::pair<int, std::string>(301, "Moved Permanently"),
    std::pair<int, std::string>(404, "Not Found"),
    std::pair<int, std::string>(410, "Gone"),
    std::pair<int, std::string>(409, "Conflict")
};

const std::unordered_map<std::string, const char *> pg::util::HTTP_TYPENAME_OF_FSUFFIX = {
    std::pair<std::string, const char *>(".html", pg::util::HTTP_CT_HTML),
    std::pair<std::string, const char *>(".txt", pg::util::HTTP_CT_PLAIN_TEXT),
    std::pair<std::string, const char *>(".xml", pg::util::HTTP_CT_XML),
    std::pair<std::string, const char *>(".gif", pg::util::HTTP_CT_GIF),
    std::pair<std::string, const char *>(".jpg", pg::util::HTTP_CT_JPG),
    std::pair<std::string, const char *>(".png", pg::util::HTTP_CT_PNG),
    std::pair<std::string, const char *>(".mp4", pg::util::HTTP_CT_MP4),
    std::pair<std::string, const char *>(".ico", pg::util::HTTP_CT_ICO),
    std::pair<std::string, const char *>(".*", pg::util::HTTP_CT_BIN),
};

const char * pg::util::stringUtil::getline(char * buf, const char * str, const char * flag) {
    const char * end = strstr(str, flag);
    if (end == NULL) return end;

    strncpy(buf, str, end - str);

    return end;
}

pg::type::Group<std::string> pg::util::stringUtil::split(const std::string & str, const char * splitFlag, int mode) {
    pg::type::Group<std::string> res;
    const char * begin = str.c_str();
    const int len = strlen(splitFlag);
    
    const char * startPtr = str.c_str();
    const char * endPtr = strstr(startPtr, splitFlag);
    
    while (endPtr != NULL) {
        switch (mode) {
        case -1 :
            res.emplace_back(startPtr, endPtr + len); break;
        case 0 :
            res.emplace_back(startPtr, endPtr); break;
        case 1 :
            res.emplace_back(startPtr == begin ? startPtr : startPtr - len, endPtr);
        }
        // res.emplace_back(startPtr, endPtr);
        startPtr = endPtr + len;
        endPtr = strstr(startPtr, splitFlag);
    }

    switch (mode) {
    case 0 :
    case -1 :
        res.emplace_back(startPtr); break;
    case 1 :
        res.emplace_back(startPtr - len); break;
    }

    return res;
}

pg::type::Group<std::string> pg::util::stringUtil::split(const std::string & str, const char ch, int mode) {
    pg::type::Group<std::string> res;
    std::string * ptr = nullptr;
    res.push_back(std::string());
    ptr = &res.back();
    
    for (std::string::const_iterator iter = str.begin(), end = str.end(); iter != end; ++iter) {
        if (*iter == ch) {
            switch (mode) {
            case -1 :
                ptr->push_back(ch);
            case 0 :
                res.emplace_back();
                break;
            case 1 :
                res.emplace_back(1, ch);
                break;
            default: break;
            }
            ptr = &res.back();
        } else ptr->push_back(*iter);
    }

    return res;
}