#include "cfg.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using std::begin, std::end, std::rbegin, std::rend;
using std::cout, std::endl;

namespace
{

	std::string trim_ws(const std::string &str)
	{
		auto iter1 = std::find_if(begin(str), end(str), [](char c) {
			return !isspace(c);
		});
		auto iter2 = std::find_if(rbegin(str), rend(str), [](char c) {
			return !isspace(c);
		});
		return std::string(iter1, iter2.base());
	}

	std::string trim_dblquote(const std::string &str)
	{
		if (str.size() > 2 && str.front() == '\"' && str.back() == '\"')
		{
			return str.substr(1, str.size() - 2);
		}
		return str;
	}

	void parse_line(const std::string &line, std::string &out_key, std::string &out_val)
	{
		auto pos = line.find_first_of('=');
		if (pos != std::string::npos)
		{
			std::string tmp_key = line.substr(0, pos);
			std::string tmp_val = line.substr(pos + 1);
			out_key = trim_dblquote(trim_ws(line.substr(0, pos)));
			out_val = trim_dblquote(trim_ws(line.substr(pos + 1)));
		}
		else
		{
			out_key.clear();
			out_val = trim_dblquote(trim_ws(line));
		}
	}

	void assign_props(Cfg &cfg)
	{
		cfg.values = Cfg::Values();
		std::multimap<std::string, std::string>::iterator iter;
		
		if (iter = cfg.contents.find("nw_name"); iter != end(cfg.contents))
		{
			cfg.values.nw_name = iter->second;
		}
		if (iter = cfg.contents.find("nw_port"); iter != end(cfg.contents))
		{
			cfg.values.nw_port = strtol(iter->second.c_str(), nullptr, 10);
		}
		if (iter = cfg.contents.find("web_root"); iter != end(cfg.contents))
		{
			cfg.values.web_root = iter->second;
		}
	}

} //namespace

bool ReadCfg(const char *cfg_file_path, Cfg &out_cfg)
{
	std::ifstream ifs;
	ifs.open(cfg_file_path);
	if (!ifs.is_open())
	{
		cout << "error: file note found. " << (cfg_file_path ? cfg_file_path : "null") << endl;
		return false;
	}

	return ReadCfg(ifs, out_cfg);
}

bool ReadCfg(std::istream &strm, Cfg &out_cfg)
{
	std::string line;
	while (!strm.eof())
	{
		std::getline(strm, line);
		line.erase(std::remove_if(begin(line), end(line), [](char c) {
					   return (c == '\r' || c == '\n');
				   }),
				   end(line));
		//cout << "line: \"" << line << "\"" << endl;
		std::string key, val;
		parse_line(line, key, val);
		if (!key.empty() || !val.empty())
		{
			if (!key.empty())
			{
				cout << "[key=val] \"" << key << "=" << val << "\"" << endl;
			}
			else
			{
				cout << "[val] \"" << val << "\"" << endl;
			}
			out_cfg.contents.insert({key, val});
		}
	}

	assign_props(out_cfg);

	return true;
}
