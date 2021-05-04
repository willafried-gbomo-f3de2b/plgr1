#include "log.h"


namespace Log {

namespace detail {

//std::mutex LogMtx;

} //namespace detail

} //namespace Log

void f() { Log::Log("abc"); }
