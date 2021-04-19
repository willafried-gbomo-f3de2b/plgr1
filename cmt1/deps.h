#pragma once

#include <matroska/FileKax.h>

#include <sqlite3/sqlite3ext.h>



#ifdef _WIN32
#define UPNP_USE_MSVCPP
#endif

#define DEPS_STATIC 1

#if defined DEPS_STATIC && DEPS_STATIC
#define FLAC__NO_DLL
#endif
#include <FLAC/all.h>
#undef FLAC__NO_DLL

#include <upnp/upnp.h>