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
			cout << "line:" << num_lines << "(" << line.size() << "): "
				<< line << "|" << endl;

			str_t key, val;
			ParseLine(line, key, val);
		}

		return true;
	}


	void ParseLine(const sv_t& line, str_t& out_key, str_t& out_val)
	{
		using std::cout , std::endl;
		typename sv_t::const_iterator first_end, sep, second_start, end_content;
		first_end = sep = second_start = end_content = line.cend();
		typename sv_t::value_type quote = 0;
		int escape = 0;

		for (auto iter = line.cbegin(), iter2 = line.cbegin();
			iter != line.cend() && end_content == line.cend();
			iter2 = iter++,
			escape = (escape == 0 || escape == 2) ? 0 : 2)
		{
			if (escape == 0) {
				switch (*iter) {
				case '"': case '\'':
					if (quote == 0) {
						quote = *iter;
					}
					else if (quote == *iter) {
						quote = 0;
					}
					break;
				case '=':
					if (quote == 0) {
						sep = iter;
					}
					break;
				case '#':
					if (quote == 0) {
						end_content = iter;
					}
					break;
				case '\\':
					escape = 1;
					break;
				}
			}
		}

		if (end_content != line.cend()) {
			cout << "w/ comment: " << sv_t(&*end_content) << endl;
		}
		if (sep != line.cend()) {
			cout << "key=" << sv_t(&*line.cbegin(), sep - line.cbegin()) 
				<< ", val=" << sv_t(&*sep, end_content - sep) << endl;
		}

		cout << "e" << endl;
	}

};


} //namespace Cfg2::detail
