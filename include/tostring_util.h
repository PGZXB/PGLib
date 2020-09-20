#ifndef __TOSTRING_UTIL_H__
#define __TOSTRING_UTIL_H__

#include <string>
#include <type_traits>
#include <iterator>

        #include <typeinfo>
        #include <iostream>

namespace pg::util::stringUtil::__IN_fmtUtil {
    // template<typename _Type>
        // std::string transToString(const _Type& ele, const std::string & limit);

    // bool	布尔型	-
    // char	字符型	8 bit
    // wchar_t	宽字符型	16 bit
    // short	短整型	16 bit
    // int	整形	16 bit
    // long	长整型	32 bit
    // long long	长整型	64 bit
    // float	单精度浮点型	6位有效数字
    // double	双精度浮点型	10位有效数字
    // long double	扩展精度浮点型	10位有效数字
#if __cplusplus >= 201703L// c++17 or gnu++11
    using std::void_t;
#else
    template<typename...> using void_t = void;
#endif

    template <typename _Type, typename _Iter = void_t<>>
    struct has_iterator : public std::false_type {
    };

    template <typename _Type>
    struct has_iterator<_Type, void_t<typename _Type::iterator>> : public std::true_type {
    };

    std::string transToString(const int & ele, const std::string & limit) {
        char buf[20] = { 0 };
        char fmt[10] = { 0 };
        sprintf(fmt, "%%%sd", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const bool & ele, const std::string &) {
        return ele ? "true" : "false";
    }

    std::string transToString(const char& ele, const std::string &) {
        return std::string() + ele;
    }

    std::string transToString(const short & ele, const std::string & limit) {
        char buf[20] = { 0 };
        char fmt[10] = { 0 };
        sprintf(fmt, "%%%shd", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const long & ele, const std::string & limit) {
        char buf[40] = { 0 };
        char fmt[20] = { 0 };
        sprintf(fmt, "%%%sld", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const long long & ele, const std::string & limit) {
        char buf[40] = { 0 };
        char fmt[20] = { 0 };
        sprintf(fmt, "%%%slld", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const float & ele, const std::string & limit) {
        char buf[40] = { 0 };
        char fmt[20] = { 0 };
        sprintf(fmt, "%%%sf", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const double & ele, const std::string & limit) {
        char buf[40] = { 0 };
        char fmt[20] = { 0 };
        sprintf(fmt, "%%%slf", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    std::string transToString(const long double & ele, const std::string & limit) {
        char buf[50] = { 0 };
        char fmt[30] = { 0 };
        sprintf(fmt, "%%%sllf", limit.c_str());
        int len = sprintf(buf, fmt, ele);
        return std::string().assign(buf, len);
    }

    // string, const char*
    template<typename _Type>
    std::enable_if_t<has_iterator<_Type>::value, std::string> transToString(const _Type& ele, const std::string & limit) {
        std::string res("[");
        typedef typename _Type::const_iterator Iter;

        for (
            Iter iter = ele.begin(), end = ele.end();
            iter != end;
            ++iter
        ) {
            res.append( transToString(*iter, std::string()) ).append(", ");
        }

        res.pop_back();
        res.back() = ']';
        return res;
    }

    template<typename _Type>
    std::enable_if_t<!has_iterator<_Type>::value, std::string> transToString(const _Type& ele, const std::string &) {  // temp-function to show
        return "<default-string>";
    }

} // namespace pg::util::stringUtl::__IN_fmtUtil


#endif