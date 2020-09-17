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
            namespace __IN_fmtUtil {
                std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>> 
                    parseBracket(
                        const std::string & str, const char * leftBracket, const char * rightBracket);
                
                template<typename _Type>
                std::string transToString(const _Type& ele, const std::string & limit = std::string());
                
                template<typename..._Args>
                std::vector<std::string> parseArgs(
                    const std::vector<std::string>& limits, const _Args&... args);

                template<typename _First, typename..._Args>
                void __IN_parseArgs(
                    std::vector<std::string> & res, 
                    const std::vector<std::string>& limits, 
                    std::vector<std::string>::const_iterator & limStrIter,
                    const _First& fArg, const _Args&... args);

                void __IN_parseArgs(
                    std::vector<std::string> & res, 
                    const std::vector<std::string> & limits, 
                    std::vector<std::string>::const_iterator & limStrIter);
                

                template<typename _Type>
                std::string transToString(const _Type& ele, const std::string & limit) {  // temp-function to show
                    return "[[[[TEST]]]]" + limit;
                }
                
                template<typename..._Args>
                std::vector<std::string> parseArgs(
                    const std::vector<std::string>& limits, const _Args&... args) {
                    std::vector<std::string> res;
                    std::vector<std::string>::const_iterator iter = limits.begin();
                    // __IN_parseArgs(res, limits, iter, args...);

                    return res;
                }

                template<typename _First, typename..._Args>
                void __IN_parseArgs(
                    std::vector<std::string> & res, 
                    const std::vector<std::string>& limits, 
                    std::vector<std::string>::const_iterator & limStrIter,
                    const _First& fArg, const _Args&... args
                    ) {
                    
                    // res.push_back(transToString(fArg/*, *++limStrIter*/));
                    if (limStrIter == limits.end()) return;
                    // __IN_parseArgs(res, limits, limStrIter, args...);
                    if (sizeof...(args) == 0) return;
                }

                void __IN_parseArgs(
                    std::vector<std::string> & res, 
                    const std::vector<std::string>& limits, 
                    std::vector<std::string>::const_iterator & limStrIter
                    ) { }
            } // namespace __IN_fmtUtil     
            
            const char * getline(char * buf, const char * str, const char * flag = CRLF);
            
            pg::type::Group<std::string> split(const std::string & str, const char * splitFlag, int mode = 0);
            pg::type::Group<std::string> split(const std::string & str, const char ch, int mode = 0);


            template<typename..._Args>
            std::string format(const std::string & fmt, _Args&& ...args) {
                // {[no]:[limit]}, 
                // fmt string : "I am your {0:3}"  <-- "father"  ==> "I am your fat"
                // fmt int/long/... : "I am {0:} years old." <-- 10  ==> "I am 10 years old."
                // fmt int/long/... : "I am {0:2} years old." <-- 99999  ==> "I am 99 years old."
                // fmt int/long/... : "I am {0:3} years old." <-- 10  ==> "I am 010 years old."
                // fmt float/double/... : "{0:.2}"  <-- 2.34343  ==> "2.34"
                // fmt other , need Function : 
                //      transToString(Type obj, string limit = "") -> string
                // example1 "Hello {}, I am {} years old. See {}", "World", 10, Point(10, 10)
                //      ==> "Hello World, I am 10 years old. See (10, 10)"
                // example2 "{0}, {1}, {1}, {0}", 1, 2
                //      ==> "1, 2, 2, 1"
                // std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>>
                    // contentRangeInBracket = __IN_fmtUtil::parseBracket(fmt);
                return std::string();
            }

        } // namespace stringUtls
        
    } // namespace util

} // namespace pg


#endif