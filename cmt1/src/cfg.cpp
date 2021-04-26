#include "cfg.h"

#include <iostream>
#include <fstream>

Cfg g_Cfg;

using std::cout, std::endl;

bool ReadCfg(const char* cfg_path)
{
    std::ifstream ifs;
    ifs.open(cfg_path, std::ios::in);
    if (!ifs.is_open()) {
        return false;
    }

    std::string line;
    while (!ifs.eof()) {
        std::getline(ifs, line);
        cout << "line: " << line << endl;

        auto pos = line.find_first_of('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            while (key.size() && isspace(key.back())) key.pop_back();
            while (key.size() && isspace(key.front())) key.erase(std::begin(key));
            //cout << "key=" << key << endl;
            std::string val = line.substr(pos + 1);
            while (val.size() && isspace(val.back())) val.pop_back();
            while (val.size() && isspace(val.front())) val.erase(std::begin(val));
            //cout << "val=" << val << endl;
            cout << "key=val:\"" << key << "=" << val << "\"" << endl;
        } else {

        }
    }
}

