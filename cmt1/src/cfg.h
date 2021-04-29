#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <locale>
#include <string_view>
#include <vector>

namespace Cfg {

namespace detail {
template <class> struct CfgReader;
} // namespace detail


template <class CharT, class CB>
bool ReadCfg(std::basic_istream<CharT>& strm, CB callback)
{
	detail::CfgReader<CharT> cfg(strm);
	return cfg.Read(callback);
}


template <class CharT = char, class CB> 
bool ReadCfg(const char* path, CB callback)
{
	std::basic_ifstream<CharT> ifs;
	ifs.open(path);
	if (!ifs.is_open())
		return false;
	return ReadCfg(ifs, callback);
}

} // namespace Cfg


namespace Cfg::detail {

template <class CharT> struct CfgReader
{
	typedef std::basic_string<CharT> str_t;
	typedef std::basic_string_view<CharT> sv_t;

	std::basic_istream<CharT>& m_strm;

	CfgReader(std::basic_istream<CharT>& s) : m_strm(s) {}

	template <class CB> bool Read(CB callback)
	{
		std::vector<CharT> buf(10 * 1024);
		int num_lines = 0;

		while (!m_strm.eof()) {
			num_lines++;

			// read a line
			auto len = m_strm.getline(buf.data(), buf.size()).gcount();
			sv_t line(buf.data());

			// remove preceding/trailing spaces, if any
			SvTrimSpaces(line);

			// skip if line is empty
			if (!line.size())
				continue;

			// get key-value pair from line
			str_t key, val;
			ParseLine(line, key, val);

			// skip if both key & value are empty 
			if (key.empty() && val.empty())
				continue;

			// return if callback returns false
			if (!callback(key.empty() ? nullptr : key.c_str(), val.c_str()))
				return false;
		}

		return true;
	}

	void ParseLine(const sv_t& line, str_t& out_key, str_t& out_val)
	{
		typename sv_t::const_iterator sep, end_pos;
		sep = end_pos = line.cend();
		CharT quote = 0;
		unsigned int escape = 0;

		for (auto iter = line.cbegin();
			iter != line.cend() && end_pos == line.cend();
			iter++, escape >>= 1)
		{
			if (escape != 0)
				continue;

			if (quote == 0) {
				switch (*iter) {
				case '"': case '\'':
					quote = *iter;
					break;
				case '=':
					sep = iter;
					break;
				case '#':
					end_pos = iter;
					break;
				}
			}
			else {
				switch (*iter) {
				case '"': case '\'':
					if (*iter == quote) {
						quote = 0;
					}
					break;
				}
			}

			if (*iter == '\\') {
				escape = 2;
			}
		}

		sv_t val;
		if (sep != line.cend()) {
			sv_t key(&line.front(), sep - line.cbegin());
			out_key = SvTrimSpaces(key);

			if (++sep != line.cend()) {
				sv_t val(&*sep, end_pos - sep);
				val = out_val = SvTrimSpaces(val);
			}
		}
		else {
			out_key.clear();

			if (line.size()) {
				sv_t val(&line.front(), end_pos - line.cbegin());
				out_val = SvTrimSpaces(val);
			}
		}
	}

	sv_t& SvTrimSpaces(sv_t& sv)
	{
		while (sv.size() && isspace(sv.front()))
			sv.remove_prefix(1);
		while (sv.size() && isspace(sv.back()))
			sv.remove_suffix(1);
		return sv;
	}
};


} //namespace Cfg::detail
