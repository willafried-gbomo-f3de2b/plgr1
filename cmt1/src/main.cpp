
#include "deps.h"

#include <iostream>
#include <string>

using std::cout, std::endl;

int main(void)
{
    cout << "main()." << endl;

    const char *locstr = setlocale(LC_ALL, "");
    cout << "locale: " << locstr << endl;

    matroska_init();

    sqlite3_initialize();

    std::string ifname = "VPN 第二";
    std::string logname = "pupnp1.log";

    UpnpLog *upnplog = UpnpLog_new();
    UpnpInitLog(upnplog);
    UpnpSetLogLevel(upnplog, UPNP_INFO);
    UpnpSetLogFileName(upnplog, logname.c_str());
    UpnpLib *upnplib = nullptr;
    UpnpInit2(&upnplib, ifname.c_str(), 0, logname.c_str());
    

    auto fsd = FLAC__stream_decoder_new();

    UpnpFinish(upnplib);

    cout << "main(), end." << endl;
}
