﻿
#include "deps.h"

#include "cfg.h"
#include "log.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>

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

	double d = 2.2;
	Log::Log<char, LOGLEVEL, double> log(std::cout, LOGLEVEL::Error, d);
	log.o(d, LOGLEVEL::Debug, 1.111);
	log.o(d + 0.7, LOGLEVEL::Info);
	log.o(d);

	Log::B<int> b1;
	std::thread t1([&]() {
		b1.f("abc").f("123").f("x");
		b1.f("xyz").f("321").f("y");
		});
	std::thread t2([&]() {
		b1.f("ABC").f("456").f("X");
		b1.f("XYZ").f("654").f("Y");
		});
	t1.join();
	t2.join();

	cout << "main(): end." << endl;
}
