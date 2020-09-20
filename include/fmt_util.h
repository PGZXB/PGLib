#ifndef __FMT_UTILS_H__
#define __FMT_UTILS_H__

#include <vector>
#include <string>
#include <algorithm>
#include <tostring_util.h>

namespace pg {
    namespace util {
        namespace stringUtil {
            namespace __IN_fmtUtil {
                // function-delaration(s)
                std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>> 
                    parseBracket(
                        const std::string & str, const char * leftBracket, const char * rightBracket);
                
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
                
                // function-definitions
 
                
                template<typename..._Args>
                std::vector<std::string> parseArgs(
                    const std::vector<std::string>& limits, const _Args&... args) {
                    std::vector<std::string> res;
                    std::vector<std::string>::const_iterator iter = limits.begin();
                    __IN_parseArgs(res, limits, iter, args...);

                    return res;
                }

                template<typename _First, typename..._Args>
                void __IN_parseArgs(
                    std::vector<std::string> & res, 
                    const std::vector<std::string>& limits, 
                    std::vector<std::string>::const_iterator & limStrIter,
                    const _First& fArg, const _Args&... args
                    ) {
                    res.push_back(transToString(fArg, *limStrIter));
                    ++limStrIter;
                    if (limStrIter == limits.end()) return;
                    __IN_parseArgs(res, limits, limStrIter, args...);
                }

                void __IN_parseArgs(
                    std::vector<std::string> & res,
                    const std::vector<std::string>& limits,
                    std::vector<std::string>::const_iterator & limStrIter
                    ) { }

                std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>> 
                    parseBracket(
                        const std::string & str, const char * leftBracket, const char * rightBracket) {
                        
                        std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>> res;

                        size_t pos = 0, npos = std::string::npos;
                        std::string::const_iterator begin = str.begin();
                        while (true) {
                            size_t beginPos = str.find(leftBracket, pos);
                            if (beginPos == npos) break;
                            size_t endPos = str.find(rightBracket, beginPos);
                            if (endPos == npos) break;
                            res.push_back({begin + beginPos + 1, begin + endPos});
                            pos = endPos;
                        }
                        return res;

                    }
            } // namespace __IN_fmtUtil
            
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
                typedef std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>>::iterator Iter;
                
                std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>>
                    contentRangeInBracket = __IN_fmtUtil::parseBracket(fmt, "{", "}");
                if (contentRangeInBracket.empty()) return fmt;

                std::vector<std::string> limits;
                std::vector<int> nos;
                
                for (
                    Iter iter = contentRangeInBracket.begin(), end = contentRangeInBracket.end();
                    iter != end; ++iter) {
                    
                    std::string::const_iterator partiIter =  std::find(iter->first, iter->second, ':');
                    nos.push_back(std::atoi(fmt.c_str() + (iter->first - fmt.begin())));
                    if (partiIter != iter->second)
                        limits.push_back(std::string().assign(partiIter + 1, iter->second));
                    else limits.emplace_back();
                }
                
                std::vector<std::string> contents =  __IN_fmtUtil::parseArgs(limits, args...);

                std::string res; res.append(fmt.begin(), contentRangeInBracket.front().first - 1);
                ssize_t cSize = contents.size();
                ssize_t idx = 0;
                for (ssize_t i = 0; i < static_cast<ssize_t>(nos.size()) - 1; ++i) {
                    idx = nos.at(i);
                    if (idx < cSize) res.append(contents.at(idx));
                    res.append(contentRangeInBracket.at(i).second + 1, contentRangeInBracket.at(i + 1).first - 1);
                }
                if ((idx = nos.back()) < cSize) res.append(contents.at(idx));
                res.append(contentRangeInBracket.back().second + 1, fmt.end());

                return res;
            }
        } // namespace stringUtil

    } // namespace util
    
} // namespace pg

#endif