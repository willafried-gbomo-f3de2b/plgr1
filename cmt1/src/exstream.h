#pragma once

#include <string>
#include <iostream>
#include <iomanip>


namespace exstream {

struct A {
	int n;
};

using std::cout, std::endl;

namespace detail {

template <class Strm>
class tmp
{
	typedef typename Strm::stream_type ST;
	friend Strm;

	Strm& m_strm;

	tmp(Strm& strm) : m_strm(strm)
	{
		cout << "tmp::ctor(Strm)" << endl;
	}

public:
	~tmp()
	{
		cout << "tmp::dtor(Strm)" << endl;
	}

	template <class T> tmp& operator<<(T&& t)
	{
		m_strm.shl(std::forward<T>(t));
		return *this;
	}

	tmp& operator<<(ST& (*pf)(ST&))
	{
		m_strm.shl(pf);
		return *this;
	}
};

} //namespace detail


template <class Strm>
class ostream
{
	typedef detail::tmp<ostream<Strm>> Tmp;
	friend Tmp;

public:
	ostream(Strm& strm) : m_strm(strm)
	{
		cout << "ostream::ctor(Strm)" << endl;
	}

	~ostream()
	{
		cout << "ostream::dtor(Strm)" << endl;
	}

	template <class T>
	Tmp operator<<(T&& t)
	{
		shl(std::forward<T>(t));
		return Tmp(*this);
	}

	Tmp operator<<(Strm& (*pf)(Strm&))
	{
		shl(pf);
		return Tmp(*this);
	}

private:
	typedef Strm stream_type;

	Strm& m_strm;

	template <class T> void shl(T&& t)
	{
		m_strm << std::forward<T>(t);
	}

	void shl(Strm& (*pf)(Strm&))
	{
		m_strm << pf;
	}
};


std::ostream& operator<<(std::ostream& strm, A a)
{
	strm << a.n;
	return strm;
}


} //namespace exstream
