
#include "deps.h"

#include "cfg.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::endl;

int main(void)
{
    cout << "main()::start..." << endl;

    const char *locstr = setlocale(LC_ALL, "");
    cout << "locale: " << locstr << endl;

    Cfg cfg = {};

    bool b = ReadCfg("cmt1.cfg", cfg);

    matroska_init();

    sqlite3_initialize();

    std::string ifname;
    int port = 0;
    std::string logname = "pupnp1.log";
    // std::ifstream fs;
    // fs.open("./nw-name.txt", std::ios::in | std::ios::binary);
    // if (!fs.is_open())
    // {
    //     //cout << "err: cannot open file ./nm-name.txt" << endl;
    //     cout << "file not found: ./nm-name.txt" << endl;
    // }
    // else
    // {
    //     std::getline(fs, ifname);
    //     ifname.erase(std::remove(std::begin(ifname),
    //         std::end(ifname), '\r'),
    //         std::end(ifname));
    //     fs >> port;
    // }
    ifname = cfg.values.nw_name;
    port = cfg.values.nw_port;

    UpnpLog *upnplog = UpnpLog_new();
    UpnpInitLog(upnplog);
    UpnpSetLogLevel(upnplog, UPNP_ERROR);
    UpnpSetLogFileName(upnplog, logname.c_str());
    UpnpLib *upnplib = nullptr;
    UpnpInit2(&upnplib,
              ifname.empty() ? nullptr : ifname.c_str(),
              port, logname.c_str());

    auto fsd = FLAC__stream_decoder_new();

    UpnpFinish(upnplib);

    cout << "main(): end." << endl;
}
