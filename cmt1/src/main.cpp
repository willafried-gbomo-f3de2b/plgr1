
#include "deps.h"

#include <iostream>
#include <string>


using std::cout, std::endl;

int main(void)
{
    cout << "main()." << endl;
    matroska_init();

    sqlite3_initialize();

    UpnpLib* upnplib = nullptr;
    std::string ifname = "VPN 第二";
    std::string logname = "pupnp1.log";
    UpnpInit2(&upnplib, ifname.c_str(), 0, logname.c_str());

    auto fsd = FLAC__stream_decoder_new();
    
}

