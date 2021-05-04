#pragma once 

#include <mutex>

#include <iostream>

namespace Log {

namespace detail {
inline std::mutex LogMtx;
class A{
public:
    static inline std::mutex LogMtx;
};
} //namespace detail

template <class CharT>
void Log(const CharT* str)
{
    std::lock_guard lg(detail::A::LogMtx);
    std::cout << &detail::A::LogMtx << std::endl;

}


} //namespace Log

