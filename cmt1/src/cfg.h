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


template <class CharT> struct READCFG_CALLBACK_PARAMS
{
	const CharT* key, * val;
	int line_number;
};


template <class CharT, class CB>
bool ReadCfg(std::basic_istream<CharT>& strm, CB callback, void* userdata)
{
	detail::CfgReader<CharT> cfg(strm);
	return cfg.Read(callback, userdata);
}


template <class CharT = char, class CB>
bool ReadCfg(const char* path, CB callback, void* userdata)
{
	std::basic_ifstream<CharT> ifs;
	ifs.open(path);
	if (!ifs.is_open())
		return false;
	return ReadCfg(ifs, callback, userdata);
}


template <class CharT>
std::basic_string<std::remove_const_t<CharT>> Unquote(CharT* str)
{
	std::basic_string_view<CharT> sv(str);
	if (sv.size() >= 2 && sv.front() == sv.back()) {
		if (sv.front() == '\'' || sv.front() == '"') {
			sv.remove_prefix(1); sv.remove_suffix(1);
		}
	}
	if (sv.empty()) 
		return "";
	return std::basic_string<std::remove_const_t<CharT>>(&sv.front(),
		sv.size());
}

namespace detail {

template <class CharT> struct CfgReader
{
	typedef std::basic_string<CharT> STR_T;
	typedef std::basic_string_view<CharT> SV_T;

	std::basic_istream<CharT>& m_strm;

	CfgReader(std::basic_istream<CharT>& s) : m_strm(s) {}

	template <class CB> bool Read(CB callback, void* userdata)
	{
		std::vector<CharT> buf(10 * 1024);
		int line_number = 0;

		while (!m_strm.eof()) {
			line_number++;

			// read a line
			auto len = m_strm.getline(buf.data(), buf.size()).gcount();
			SV_T line(buf.data());

			// remove preceding/trailing spaces, if any
			SvTrimSpaces(line);

			// skip if line is empty
			if (!line.size())
				continue;

			// get key-value pair from line
			STR_T key, val;
			ParseLine(line, key, val);

			// skip if both key & value are empty 
			if (key.empty() && val.empty())
				continue;

			// return if callback returns false
			READCFG_CALLBACK_PARAMS<CharT> params;
			params.key = key.empty() ? nullptr : key.c_str();
			params.val = val.c_str();
			params.line_number = line_number;
			if (!callback(&params, userdata))
				return false;
		}

		return true;
	}

	void ParseLine(const SV_T& line, STR_T& out_key, STR_T& out_val)
	{
		typename SV_T::const_iterator sep, end_pos;
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

		SV_T val;
		if (sep != line.cend()) {
			SV_T key(&line.front(), sep - line.cbegin());
			out_key = SvTrimSpaces(key);

			if (++sep != line.cend()) {
				SV_T val(&*sep, end_pos - sep);
				val = out_val = SvTrimSpaces(val);
			}
		}
		else {
			out_key.clear();

			if (line.size()) {
				SV_T val(&line.front(), end_pos - line.cbegin());
				out_val = SvTrimSpaces(val);
			}
		}
	}

	SV_T& SvTrimSpaces(SV_T& sv)
	{
		while (sv.size() && isspace(sv.front()))
			sv.remove_prefix(1);
		while (sv.size() && isspace(sv.back()))
			sv.remove_suffix(1);
		return sv;
	}
};

} // namespace detail
} // namespace Cfg
