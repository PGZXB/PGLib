#ifndef __FMT_UTILS_H__
#define __FMT_UTILS_H__

#include <vector>
#include <string>
#include <algorithm>
#include <tostring_util.h>

namespace pg::util::stringUtil {
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

    template<typename _Res, typename..._Args>
    _Res format(const std::string & fmt, _Args&& ...args) {
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

        _Res res; res.append(fmt.begin(), contentRangeInBracket.front().first - 1);
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

    template<typename _Res, typename..._Args>
    void format(_Res & res, const std::string & fmt, _Args&& ...args) {
        typedef std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>>::iterator Iter;
        
        std::vector<std::pair<std::string::const_iterator, std::string::const_iterator>>
            contentRangeInBracket = __IN_fmtUtil::parseBracket(fmt, "{", "}");
        if (contentRangeInBracket.empty()) { res = fmt; return; }

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

        res.append(fmt.begin(), contentRangeInBracket.front().first - 1);
        ssize_t cSize = contents.size();
        ssize_t idx = 0;
        for (ssize_t i = 0; i < static_cast<ssize_t>(nos.size()) - 1; ++i) {
            idx = nos.at(i);
            if (idx < cSize) res.append(contents.at(idx));
            res.append(contentRangeInBracket.at(i).second + 1, contentRangeInBracket.at(i + 1).first - 1);
        }
        if ((idx = nos.back()) < cSize) res.append(contents.at(idx));
        res.append(contentRangeInBracket.back().second + 1, fmt.end());
    }

} // namespace pg::util::stringUtil

#endif