
#include "deps.h"

#include "cfg.h"
#include "log.h"
#include "exstream.h"
#include "path.h"
#include "appcfg.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <iomanip>

using std::cout, std::endl;

bool db_init(void);

AppCfg::AppCfg g_Cfg;


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

	std::string self_path = Path::GetSelfPath();
	std::string self_dir = Path::GetSelfDir();
	std::string self_name = Path::GetSelfName();
	std::string self_base = Path::GetSelfBaseName();
	std::string self_ext = Path::GetSelfExt();

	std::string ifname;
	int port = 0;
	std::string logname = "pupnp1.log";

	std::map<std::string, std::string> cfg_map;
	bool b = Cfg::ReadCfg("../cmt1.cfg",
		[&](const Cfg::READCFG_CALLBACK_PARAMS<char>* params, void* userdata)
		{
			cout << "  [" << params->line_number << "] |";
			if (params->key)
				cout << params->key << "|";
			cout << Cfg::Unquote(params->val) << "|" << endl;

			if (params->key) {
				std::string key_str(params->key);
				std::string val_str(Cfg::Unquote(params->val));
				//g_Cfg.push_back({ params->key, params->val,
				//params->line_number
				//});
				cfg_map[key_str] = val_str;
				if (key_str == "nw_name") {
					ifname = val_str;
				}
				else if (key_str == "nw_port") {
					port = strtol(val_str.c_str(), nullptr, 10);
				}
			}
			return true;
		}, (void*)1234);

	g_Cfg = cfg_map;

	db_init();

	matroska_init();


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

	exstream::ostream o2(cout);
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


bool db_init(void)
{
	std::string db_path;
	if (auto iter = g_Cfg.find("db_path");
		iter == g_Cfg.end() || iter->second.empty())
	{
		db_path = Path::GetSelfDir() + Path::GetSepString()
			+ Path::GetSelfBaseName() + ".db";
	}
	else {
		db_path = iter->second;
	}
	cout << "db_init(): db_path=" << db_path << endl;

	sqlite3_initialize();
	sqlite3* db = nullptr;
	if (int rc = sqlite3_open(db_path.c_str(), &db); rc != 0) {
		cout << "error: sqlite3_open(), " << rc;
	}
	else {
		cout << "db: 0x" << std::hex << db << endl;
	}

	std::string sql1 = "create table tb1 ("
		"  id integer, "
		"  name string"
		");";
	std::string sql2 = "select * from tb1;";
	char* errmsg = nullptr;
	auto cb1 = [](void*, int, char**, char**) -> int {
		return 0;
	};
	if (int rc = sqlite3_exec(db, sql1.c_str(), cb1, (void*)1234, &errmsg); rc)
	{
		cout << "eer-sql1: " << rc << ", " << errmsg << endl;
	}
	if (int rc = sqlite3_exec(db, sql2.c_str(), cb1, (void*)1234, &errmsg); rc)
	{
		cout << "eer-sql2: " << rc << endl;
	}

	if (int rc = sqlite3_close(db); rc) {
		cout << "error: sqlite3_close(), " << rc;
	}

	return true;
}

