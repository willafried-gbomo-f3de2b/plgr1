#pragma once

#include <string>
#include <iostream>
#include <iomanip>


namespace exstream {

struct A {
	int n;
};

using std::cout, std::endl;

template <class Base, class Strm>
class tmp : public Base
{
public:
	tmp(Strm& strm) : Base(strm)
	{
		cout << "tmp::ctor(Strm)" << endl;
	}

	template <class T>
	tmp& operator<<(T&& t)
	{
		ls(std::forward<T>(t));
		return *this;
	}

	tmp& operator<<(Strm& (*pf)(Strm&))
	{
		ls(pf);
		return *this;
	}


};


template <class Strm>
class ostream
{
public:
	typedef tmp<ostream<Strm>, Strm> Tmp;

	Strm& m_strm;
	ostream(Strm& strm) : m_strm(strm)
	{
		cout << "ostream::ctor(Strm)" << endl;
	}

	template <class T>
	Tmp operator<<(T&& t)
	{
		ls(std::forward<T>(t));
		return Tmp(m_strm);
	}

	Tmp operator<<(Strm& (*pf)(Strm&))
	{
		ls(pf);
		return Tmp(m_strm);
	}

	template <class T>
	void ls(T&& t)
	{
		m_strm << std::forward<T>(t);
	}

	void ls(Strm& (*pf)(Strm&))
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
