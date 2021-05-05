
#include "deps.h"

#include "cfg.h"
#include "log.h"
#include "exstream.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <iomanip>

using std::cout, std::endl;


template <class CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os,
	const LOGLEVEL& level)
{
	switch (level) {
	case Error:
		os << "Error";
		break;
	case LOGLEVEL::Info:
		os << "Info";
		break;
	default:
		os << (int)level;
	}
	return os;
}



int main(void)
{
	cout << endl;
	cout << "main()::start..." << endl;

	const char* locstr = setlocale(LC_ALL, "");
	cout << "locale: " << locstr << endl;

	std::string ifname;
	int port = 0;
	std::string logname = "pupnp1.log";

	bool b = Cfg::ReadCfg("cmt1.cfg",
		[&](const Cfg::READCFG_CALLBACK_PARAMS<char>* params)
		{
			cout << "  [" << params->line_number << "] |";
			if (params->key)
				cout << params->key << "|";
			cout << Cfg::Unquote(params->val) << "|" << endl;

			if (params->key) {
				std::string key_str(params->key);
				std::string val_str(Cfg::Unquote(params->val));
				if (key_str == "nw_name") {
					ifname = val_str;
				}
				else if (key_str == "nw_port") {
					port = strtol(val_str.c_str(), nullptr, 10);
				}
			}
			return true;
		});

	matroska_init();

	sqlite3_initialize();

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

	std::cout << std::setw(8);

	exstream::A a; a.n = 555;
	exstream::ostream<std::ostream> o2(std::cout);
	o2 << std::setw(4)
		<< 123
		<< std::setw(6)
		<< "abc"
		<< a
		<< endl
		<< std::setw(4)
		<< std::endl
		<< std::hex
		<< std::setw(4)
		<< 0xff
		<< ", "
		<< std::string("abc")
		<< endl;
		//o2.operator<<(endl);



	cout << "main(): end." << endl;
}
