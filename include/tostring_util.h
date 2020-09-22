#ifndef __TOSTRING_UTIL_H__
#define __TOSTRING_UTIL_H__

#include <string>
#include <type_traits>
#include <iterator>
#include <memory>

#include <typeinfo>
#include <iostream>

namespace pg::util::stringUtil::__IN_fmtUtil {
#if __cplusplus >= 201703L
    using std::void_t;
#else
    template<typename...> using void_t = void;
#endif

    template <typename _Type, typename _Iter = void_t<>>
    struct has_iterator : public std::false_type { };

    template <typename _Type>
    struct has_iterator<_Type, void_t<typename _Type::iterator>> : public std::true_type { };

    // function-delarations
    template <typename _First, typename _Second>
    std::string transToString(const std::pair<_First, _Second> & ele, const std::string &);

    template<typename _Type>
    std::enable_if_t<has_iterator<_Type>::value, std::string> transToString(const _Type& ele, const std::string & limit);

    template<typename _Type>
    std::enable_if_t<!has_iterator<_Type>::value, std::string> transToString(const _Type& ele, const std::string &);

    // function-definitions
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

    std::string transToString(const std::string & ele, const std::string & limit) {
        struct HeapCharArrayWrapper {  // temp-tool
            HeapCharArrayWrapper(char * arr) : ptr(arr) { }
            ~HeapCharArrayWrapper() { if (ptr != nullptr) delete [] ptr; }
            char * ptr = nullptr;
        };

        HeapCharArrayWrapper buf(new char[ele.size() << 1]);  // temp-processing ==> Buffer
        char fmt[50] = { 0 };

        sprintf(fmt, "%%%ss", limit.c_str());
        sprintf(buf.ptr, fmt, ele.c_str());
        return std::string(buf.ptr);
    }

    template <typename _First, typename _Second>
    std::string transToString(const std::pair<_First, _Second> & ele, const std::string &) {
        const std::string NULL_STRING;
        return std::string()
            .append(transToString(ele.first, NULL_STRING))
            .append(" : ")
            .append(transToString(ele.second, NULL_STRING));
    }

    // string, const char*
    template<typename _Type>
    std::enable_if_t<has_iterator<_Type>::value, std::string> transToString(const _Type& ele, const std::string & limit) {
        typedef typename _Type::const_iterator Iter;
        
        const std::string NULL_STRING;
        std::string res("[");

        for (
            Iter iter = ele.begin(), end = ele.end();
            iter != end;
            ++iter
        )
            res.append( transToString(*iter, NULL_STRING) ).append(", ");  // useless second-param

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