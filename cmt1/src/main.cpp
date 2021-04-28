
#include "deps.h"

#include "cfg.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::endl;

int main(void)
{
	cout << "main()::start..." << endl;

	const char* locstr = setlocale(LC_ALL, "");
	cout << "locale: " << locstr << endl;

	//Cfg cfg = {};

	//bool b = ReadCfg("cmt1.cfg", cfg);
	bool b = Cfg::ReadCfg("cmt1.cfg");

	matroska_init();

	sqlite3_initialize();

	std::string ifname;
	int port = 0;
	std::string logname = "pupnp1.log";

	// ifname = cfg.values.nw_name;
	// port = cfg.values.nw_port;

	UpnpLog* upnplog = UpnpLog_new();
	UpnpInitLog(upnplog);
	UpnpSetLogLevel(upnplog, UPNP_ERROR);
	UpnpSetLogFileName(upnplog, logname.c_str());
	UpnpLib* upnplib = nullptr;
	UpnpInit2(&upnplib,
		ifname.empty() ? nullptr : ifname.c_str(),
		port, logname.c_str());

	auto fsd = FLAC__stream_decoder_new();

	UpnpFinish(upnplib);

	cout << "main(): end." << endl;
}
