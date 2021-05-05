#pragma once

#include <string>


namespace exstream {

template <class charT, class traits = std::char_traits<charT>>
class basic_ostream
{
public:
    basic_ostream<charT, traits>& operator<<(bool n)
    {
        cout << "bool" << endl;
        return *this;
    }

    basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>&
        (*pf)(std::basic_ostream<charT, traits>&))
    {
        cout << "pf(ostream)" << endl;
        return *this;
    }
};

template <class charT, class traits = std::char_traits<charT>>
class ostream2 : public basic_ostream<charT, traits>
{
public:
    template <class T> ostream2& operator<<(T&& t)
    {
        cout << "post T" << endl;
        basic_ostream::operator<<(std::forward<T>(t));
        return *this;
    }

    basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>&
        (*pf)(std::basic_ostream<charT, traits>&))
    {
        cout << "post pf(ostream)" << endl;
        basic_ostream::operator<<(pf);
        return *this;
    }
};

} //namespace exstream
