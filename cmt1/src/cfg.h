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

template <class T> bool ReadCfg(std::basic_istream<T>& strm)
{
	detail::CfgReader<T> cfg(strm);
	return cfg.Read();
}

template <class T> bool ReadCfg(const T* path)
{
	std::basic_ifstream<T> ifs;
	ifs.open(path);
	if (!ifs.is_open())
		return false;
	return ReadCfg<T>(ifs);
}

} // namespace Cfg

namespace Cfg::detail {

template <class T> struct CfgReader 
{
	typedef std::basic_string<T> str_t;
	typedef std::basic_string_view<T> sv_t;

	std::basic_istream<T>& m_strm;

	CfgReader(std::basic_istream<T>& s) : m_strm(s) {}

	bool Read(void)
	{
		using std::cout, std::endl;

		std::vector<T> buf(10 * 1024);
		int num_lines = 0;
		while (!m_strm.eof()) {
			num_lines++;

			// read a line
			auto len = m_strm.getline(buf.data(), buf.size()).gcount();
			sv_t line(buf.data());

			// remove trailing spaces, if any
			while (line.size() && std::isspace(line.back(), std::locale()))
				line.remove_suffix(1);

			// remove preceding spaces, if any
			while (line.size() && std::isspace(line.front(), std::locale()))
				line.remove_prefix(1);

			if (!line.size())
				continue;
			cout << "line:" << num_lines << "(" << line.size() << "): "
				<< line << "|" << endl;

			str_t key, val;
			ParseLine(line, key, val);

			if (key.size()) {
				cout << "  key:" << key << "|";
			}
			cout << "  val:" << val << "|" << endl;
		}

		return true;
	}

	void ParseLine(const sv_t& line, str_t& out_key, str_t& out_val)
	{
		typename sv_t::const_iterator sep, end_pos;
		sep = end_pos = line.cend();
		T quote = 0;
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


} //namespace Cfg2::detail
