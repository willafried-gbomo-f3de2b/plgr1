#pragma once

#include <string>
#include <istream>
#include <map>

struct Cfg
{
    struct Values
    {
        std::string nw_name;
        int nw_port;
        std::string web_root;
    } values;

    std::multimap<std::string, std::string> contents;
};

bool ReadCfg(const char *cfg_file_path, Cfg &out_cfg);
bool ReadCfg(std::istream &strm, Cfg &out_cfg);
