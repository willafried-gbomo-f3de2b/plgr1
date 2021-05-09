#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>


namespace AppCfg {

inline namespace v2 {

typedef std::map<std::string, std::string> AppCfg;

} //inline namespace v2


namespace v1 {

template <class charT> struct AppCfgEntry
{
    std::basic_string<charT> key;
    std::basic_string<charT> val;
    int line_number;
};

template <class charT> using AppCfg = std::vector<AppCfgEntry<charT>>;


template <class charT>
const std::string& find(const AppCfg<charT>& cfg,
    const std::basic_string<charT>& key)
{
    static std::string nores;
    auto iter = std::find_if(cfg.begin(), cfg.end(), [&](const auto& x) {
        return (x.key == key);
        });
    if (iter == cfg.end())
        return nores;
    return iter->val;
}

} //namespace v1

} //namespace AppCfg


extern AppCfg::AppCfg g_Cfg;
