#include <vector>
#include <string>
//#include <iostream>
//#include <functional>
//#include <type_traits>
#include <sstream>
//#include <streambuf>

namespace dps
{
    struct{
    char32_t seperator=(char32_t)',';
    char32_t eol=(char32_t)'\n';
    char32_t quote=(char32_t)'"';
    }delimiters;

    template<typename T>void
        tokenize(std::basic_istream<T>& stream,
        T delim,
        T quoted_delim,
        std::vector<std::basic_string<T>>& out)
    {
        auto quoted_count{0};
        std::basic_stringstream<T> s;
        while(!stream.eof())
        {
            auto c=stream.get();
            if(c==quoted_delim)
            {
                quoted_count++;
                continue;
            }
            if(c==delim && !(quoted_count&1))
            {
                out.push_back(s.str());
                s.str(std::string());
                continue;
            }
            s.put(c);
        }
        out.push_back(s.str());
    }

    template<typename T> void
        join(std::basic_ostream<T>& stream,
        T delim,
        T quoted_delim,
        const std::vector<std::basic_string<T>>& strings)
    {
        auto element_count{0};
        for(const auto& s:strings)
        {
            auto quoted=s.find(delim)!=std::string::npos;
            if(element_count++)
            {
                stream<<delim;
            }
            if(quoted)stream<<quoted_delim;
            stream<<s;
            if(quoted)stream<<quoted_delim;
        }
    }
    template<typename T>std::basic_istream<T>&
        operator>>(std::basic_istream<T>& stream,
        std::vector<std::basic_string<T>>& output)
    {
        tokenize(stream,(T)delimiters.seperator,
                 (T)delimiters.quote, output);
        return stream;
    }
    template<typename T>std::basic_istream<T>&
        operator>>(std::basic_istream<T>& stream,
        std::vector<std::vector<std::basic_string<T>>>& output)
    {
        std::vector<std::basic_string<T>> lines;
        tokenize(stream,(T)delimiters.eol,
                 (T)0,lines);
        for(const auto& l:lines)
        {
            std::basic_stringstream<T> ss(l);
            std::vector<std::basic_string<T>> values;
            ss>>values;
            output.push_back(values);
        }
        return stream;
    }
    template<typename T>std::basic_ostream<T>&
        operator<<(std::basic_ostream<T>& stream,
        const std::vector<std::basic_string<T>> strings)
    {
        join(stream,(T)delimiters.seperator,
             (T)delimiters.quote,strings);
        return stream;
    }
    template<typename T>std::basic_ostream<T>&
        operator<<(std::basic_ostream<T>& stream,
        const std::vector<std::vector<std::basic_string<T>>>& output)
    {
        for(const auto& o:output)
        {
            stream<<o<<(T)delimiters.eol;
        }
        return stream;
    }
}
