#include <HttpRequest.h>
#include <utils.h>


// public-functions
pg::HttpRequest::HttpRequest(const char * msg, char * contBuf) : contentBuf(contBuf) {
    init(msg);
}

pg::HttpRequest::HttpRequest(std::string && requestMsg, char * contBuf) : contentBuf(contBuf) {
    init(requestMsg.c_str());
}

pg::HttpRequest::HttpRequest(const std::string & requestMsg, char * contBuf) : contentBuf(contBuf) {
    init(requestMsg.c_str());
}

pg::HttpRequest::~HttpRequest() { }

const std::string & pg::HttpRequest::getUrl() const {
    return url;
}

const std::string & pg::HttpRequest::getValue(const std::string & key) const {
    static const std::string null_string;

    std::map<std::string, std::vector<std::string>>::const_iterator iter = requestArgs.find(key);

    if (iter == requestArgs.end()) return null_string;
    return iter->second.front();
}

const std::vector<std::string> & pg::HttpRequest::getValues(const std::string & key) const {
    static const std::vector<std::string> null_vector;

    std::map<std::string, std::vector<std::string>>::const_iterator iter = requestArgs.find(key);
    
    if (iter == requestArgs.end()) return null_vector;
    return iter->second;
}


// protected-functions / helper-functions
void pg::HttpRequest::init(const char * msg) {
    char method[16] = { 0 };
    char fh_content[BUFSIZ] = { 0 };
    char httpVer[32] = { 0 };

    // header-lines
    const char * contPosi =  skipToContent(msg);
    if (contentBuf != nullptr)  // save content
        strcpy(contentBuf, contPosi);

    // parse the http-header
    parseHeader(headerLines.front().c_str(), method, fh_content, httpVer);

    // request-method
    if (::strcasecmp(method, "get") == 0) requestMethod = GET;
    else if (::strcasecmp(method, "post") == 0) requestMethod = POST;
    // http-vertion
    httpVertion.assign(httpVer, strlen(httpVer));
    // url & args
    char * tmp = strstr(fh_content, "?");
    url.assign(fh_content, tmp != NULL ? tmp - fh_content : strlen(fh_content));
    parseArgs(++tmp);

    // process-header by request-method
    if (requestMethod == POST)
        parseArgs(contPosi);

#if 1
    // using to Debug
    printf("Debug----->>>>   content : \"%s\"\n", contPosi);
    printf("Debug----->>>>   url : %s\n", url.data());
    for (auto & e : requestArgs) {
        std::printf("Debug----->>>>   args %s = ", e.first.data());
        for (auto & ee : e.second)
            printf("%s, ", ee.data()); 
        printf("\n");
    }
    for (int i = 0; i < headerLines.size(); ++i) {
        printf("Debug----->>>>   header-msg-line%d : \"%s\"\n", i, headerLines[i].c_str());
    }
#endif
}

void pg::HttpRequest::parseHeader(const char * header, char * method, char * content, char * httpVer) {

    sscanf(header, "%[^ ] %[^ ] %[^ ]", method, content, httpVer);
    
    // std::printf("Debug----->>>>   %s  %s  %s \n", method, content, httpVer);
}

void pg::HttpRequest::parseArgs(const char * argsMsg) {
    const char * tmp = --argsMsg;

    if (tmp != NULL) {
        std::string key;
        std::string value;
        std::string * pKV = &key;
        for (const char * i = tmp + 1; *i != '\0'; ++i) {
            if (*i == '=') pKV = &value;
            else if (*i == '&') {
                pKV = &key;
                requestArgs[key].push_back(value);
                key.clear();
                value.clear();
            } else if (*(i + 1) == '\0') {
                pKV->push_back(*i);
                requestArgs[key].push_back(value);
            }
            else pKV->push_back(*i);
        }
    }
}

const char * pg::HttpRequest::skipToContent(const char * msg) {
    const char * lastPosi = msg;

    msg = strstr(msg, util::CRLF);
    headerLines.push_back(std::string(lastPosi, msg - lastPosi));

    while (msg != NULL && msg - (lastPosi + 2 ) != 0) {
        lastPosi = msg;
        msg = strstr(msg + 2, util::CRLF);
        headerLines.push_back(std::string(lastPosi + 2, msg - (lastPosi + 2)));
    }

    return msg += 2;
}
