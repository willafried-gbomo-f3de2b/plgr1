#pragma once

#include <string>

struct Cfg
{
    std::string nw_name;
    int nw_port;
    
    std::string web_root;

};

extern Cfg g_Cfg;

bool ReadCfg(const char* cfg_path);

