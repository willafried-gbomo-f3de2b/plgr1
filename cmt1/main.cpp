
#include <matroska/FileKax.h>
#include <sqlite3/sqlite3ext.h>
#define UPNP_USE_MSVCPP
#include <upnp/upnp.h>

#include <iostream>
#include <string>


using std::cout, std::endl;

int main(void)
{
    cout << "main()." << endl;
    matroska_init();

    sqlite3_initialize();

    UpnpLib* upnplib = nullptr;
    UpnpInit2(&upnplib, nullptr, 0, nullptr);
}

