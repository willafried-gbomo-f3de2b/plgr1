#pragma once

#include <matroska/FileKax.h>

#include <sqlite3/sqlite3.h>
//#include <sqlite3/sqlite3ext.h>


#ifdef _WIN32
#define UPNP_USE_MSVCPP
#endif

#if defined DEPS_STATIC && DEPS_STATIC
#define FLAC__NO_DLL
#define UPNP_STATIC_LIB
#endif
#include <FLAC/all.h>
#include <upnp/upnp.h>
#include <upnp/UpnpLog.h>
/* req: Ws2_32.lib, Iphlpapi.lib */
#undef FLAC__NO_DLL
#undef UPNP_STATIC_LIB
