#pragma once

#include <istream>
#include <fstream>
#include <vector>
#include <string_view>
#include <locale>

namespace Cfg2
{
	namespace detail
	{
		template <class>
		struct Cfg;
	} //namespace detail

	template <class T>
	bool ReadCfg(const T *path)
	{
		std::basic_ifstream<T> ifs;
		ifs.open(path);
		if (!ifs.is_open())
			return false;
		return ReadCfg<T>(ifs);
	}

	template <class T>
	bool ReadCfg(std::basic_istream<T> &strm)
	{
		detail::Cfg<T> cfg(strm);

		return cfg.Read();
	}

} //namespace Cfg2

namespace Cfg2::detail
{
	template <class T>
	struct Cfg
	{
		std::basic_istream<T> &m_strm;

		Cfg(std::basic_istream<T> &s) : m_strm(s) {}

		bool Read(void)
		{
			using std::cout, std::endl;

			std::vector<T> buf(10 * 1024);

			while (!m_strm.eof())
			{
				// skip first spaces
				std::ws(m_strm);

				// read a line
				auto len = m_strm.getline(buf.data(), buf.size())
							   .gcount();
				std::basic_string_view<T> sv(buf.data());

				// remove CR, LF, if any
				while (sv.size() &&
					   (sv.back() == '\r' || sv.back() == '\n'))
					sv.remove_suffix(1);

				// remove trailing spaces, if any
				while (sv.size() && std::isspace(sv.back(), std::locale #()))
					sv.remove_suffix(1);
				cout << "sv (" << sv.size() << "): " << sv << "|" << endl;
			}

			return true;
		}
	};
} //namespace Cfg2::detail
