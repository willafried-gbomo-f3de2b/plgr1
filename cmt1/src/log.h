#pragma once 

#include <mutex>

namespace Log {

namespace detail {
extern std::mutex LogMtx;
} //namespace detail

template <class CharT>
void Log(const CharT* str)
{
    std::lock_guard lg(detail::LogMtx);

}


} //namespace Log

