
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
	sqlite3* db = nullptr;
	std::string db_path = "cmt1.db";
	if (int rc = sqlite3_open(db_path.c_str(), &db); rc != 0) {
		cout << "error: sqlite3_open(), " << rc;
	} else {
		cout << "db: 0x" << std::hex << db << endl;
	}
	// sqlite3_exec
	if (int rc = sqlite3_close(db); rc) {
		cout << "error: sqlite3_close(), " << rc;
	}

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

	std::vector<std::thread> v1;
	for (int i = 0; i < 20; i++) {
		v1.push_back(std::thread([&v1, &o2]() {
			o2 << std::dec << "123" << 456 << endl;
			}));
		v1.push_back(std::thread([&v1, &o2]() {
			o2 << "abc" << "def" << "hij" << endl;
			}));
		v1.push_back(std::thread([&v1, &o2]() {
			o2 << std::hex << std::setfill('0') << std::setw(4) << 0x0123
				<< 0x4567 << "89ab" << 0xcdef << endl;
			}));
	}

	for (auto& x : v1) {
		x.join();
	}

	cout << "main(): end." << endl;
}
