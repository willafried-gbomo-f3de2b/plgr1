#pragma once

#include <string>
#include <iostream>
#include <iomanip>


namespace exstream {

using std::cout, std::endl;

template <class charT, class traits = std::char_traits<charT>>
class basic_ostream : public std::basic_ostream<charT, traits>
{
public:
    basic_ostream() : std::basic_ostream<charT, traits>(std::cout.rdbuf())
    {}

    // template <class V>
    // basic_ostream<charT, traits>& operator<<(V&& v)
    // {
    //     cout << "basico V&&" << endl;
    //     std::basic_ostream<charT, traits>::operator<<(std::forward<V>(v));
    //     return *this;
    // }

    // basic_ostream<charT, traits>& operator<<(bool n)
    // {
    //     cout << "bool" << endl;
    //     return *this;
    // }

    // basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>&
    //     (*pf)(std::basic_ostream<charT, traits>&))
    // {
    //     cout << "pf(ostream)" << endl;
    //     return *this;
    // }
};

template <class charT, class traits = std::char_traits<charT>>
class ostream2 : public basic_ostream<charT, traits>
{
public:
    template <class V> ostream2& operator<<(V&& t)
    {
        cout << "post V" << endl;
        std::basic_ostream<charT, traits>::operator<<(std::forward<V>(t));
        return *this;
    }

    ostream2& operator<<(std::basic_ostream<charT, traits>&
        (*pf)(std::basic_ostream<charT, traits>&))
    {
        cout << "post pf(ostream)" << endl;
        basic_ostream<charT, traits>::operator<<(pf);
        return *this;
    }
};

} //namespace exstream
