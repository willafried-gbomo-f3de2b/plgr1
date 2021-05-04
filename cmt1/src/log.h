#pragma once 

#include <mutex>

#include <iostream>


namespace Log {

using std::cout, std::endl;


template <class CharT, class ...Args> struct Log2
{
    Log2()
    {
        cout << "template <" << typeid(CharT).name() << ", class ...Args("
            << sizeof...(Args) << ")> struct Log2" << endl;
        cout << "  - Log2::ctor()" << endl;
    }
    std::mutex m_Mtx;
};


template <class CharT, class T, class ...Args>
struct Log2<CharT, T, Args...> : Log2<CharT, Args...>
{
    typedef Log2<CharT, Args...> base;

    template <class V0, class ...Vs>
    Log2(V0&& v0, Vs&& ...vs) : base(std::forward<Vs>(vs)...), m_def(v0)
    {
        cout << "template <" << typeid(CharT).name() << ", "
            << typeid(T).name() << ", class ...Args(" << sizeof...(Args)
            << ")> struct Log2<" << typeid(CharT).name() << ", "
            << typeid(T).name() << ", Args...(" << sizeof...(Args)
            << ")> : Log2<" << typeid(CharT).name() << ", Args...("
            << sizeof...(Args) << ")>" << endl;
        cout << "  - Log2::ctor(" << v0 << ", Vs...(" << sizeof...(Vs) << "))"
            << endl;
    }

    T m_def;
};


template <class CharT, class ...Args>
struct Log : Log2<CharT, Args...>
{
    template <class ...Vs>
    Log(Vs&& ...vs) : Log2(std::forward<Vs>(vs)...)
        // Log(Args&& ...args) : Log2(std::forward<Args>(args)...)
    {
        cout << "template <" << typeid(CharT).name() << ", class ...Args("
            << sizeof...(Args) << ")> struct Log : Log2<"
            << typeid(CharT).name() << ", Args...(" << sizeof...(Args)
            << ")>" << endl;
        cout << "  - Log::ctor(Vs...(" << sizeof...(Vs) << "))" << endl;
    }
};


} //namespace Log

