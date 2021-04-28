#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <locale>
#include <string_view>
#include <vector>

namespace Cfg2 {

namespace detail {

template <class> struct Cfg;

} // namespace detail

template <class T> bool ReadCfg(std::basic_istream<T>& strm);

template <class T> bool ReadCfg(const T* path)
{
	std::basic_ifstream<T> ifs;
	ifs.open(path);
	if (!ifs.is_open())
		return false;
	return ReadCfg<T>(ifs);
}

template <class T> bool ReadCfg(std::basic_istream<T>& strm)
{
	detail::Cfg<T> cfg(strm);
	return cfg.Read();
}

} // namespace Cfg2

namespace Cfg2::detail {

template <class T> struct Cfg {
	typedef std::basic_string<T> str_t;
	typedef std::basic_string_view<T> sv_t;

	std::basic_istream<T>& m_strm;

	Cfg(std::basic_istream<T>& s) : m_strm(s) {}

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
			cout << "line:" << num_lines << "(" << line.size() << "): " << line << "|"
				<< endl;

			str_t key, val;
			ParseLine(line, key, val);
		}

		return true;
	}


	void ParseLine(const sv_t& line, str_t& out_key, str_t& out_val)
	{
		sv_t::const_iterator first_end, sep, second_start, end_content;
		first_end = sep = second_start = end_content = line.cend();
		sv_t::value_type cur_quote = 0;
		bool escape = false;

		auto iter = line.cbegin();
		for (auto iter = line.cbegin(); iter != line.cend(); ) {

		}
	}

};


} //namespace Cfg2::detail
