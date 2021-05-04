#pragma once 

#include <mutex>

#include <iostream>


enum LOGLEVEL {
	Fatal, Error, Warn, Info, Debug
};



namespace Log {

using std::cout, std::endl;


template <class CharT, class ...Args> struct Log2
{
	Log2()
	{
		cout << "template <" << typeid(CharT).name() << ", class ...Args("
			<< sizeof...(Args) << ")> struct Log2" << endl;
		cout << "  - Log2::ctor()" << endl;
	}
	inline static std::mutex m_mtx;

	void o(std::ostream& strm)
	{
		strm << "";
	}
};


template <class CharT, class T, class ...Args>
struct Log2<CharT, T, Args...> : Log2<CharT, Args...>
{
	typedef Log2<CharT, Args...> base;

	template <class V0, class ...Vs>
	Log2(V0&& v0, Vs&& ...vs) : base(std::forward<Vs>(vs)...), m_def(v0)
	{
		cout << "template <" << typeid(CharT).name() << ", "
			<< typeid(T).name() << ", class ...Args(" << sizeof...(Args)
			<< ")> struct Log2<" << typeid(CharT).name() << ", "
			<< typeid(T).name() << ", Args...(" << sizeof...(Args)
			<< ")> : Log2<" << typeid(CharT).name() << ", Args...("
			<< sizeof...(Args) << ")>" << endl;
		cout << "  - Log2::ctor(" << v0 << ", Vs...(" << sizeof...(Vs) << "))"
			<< endl;
	}

	T m_def;

	template <class V0, class ...Vs>
	void o(std::ostream& strm, V0&& v0, Vs&& ...vs)
	{
		strm << "[" << v0 << "] ";
		base::o(strm, std::forward<Vs>(vs)...);
	}

	template <class ...Vs>
	void o(std::ostream& strm, Vs&& ...vs)
	{
		strm << "[" << m_def << "] ";
		base::o(strm);
	}


};



template <class CharT, class ...Args>
struct Log : Log2<CharT, Args...>
{
	typedef Log2<CharT, Args...> base;
	typedef Log<CharT, Args...> LOG_T;

	template <class ...Vs>
	Log(std::ostream& strm, Vs&& ...vs) : Log2(std::forward<Vs>(vs)...),
		m_strm(strm)
	{
		cout << "template <" << typeid(CharT).name() << ", class ...Args("
			<< sizeof...(Args) << ")> struct Log : Log2<"
			<< typeid(CharT).name() << ", Args...(" << sizeof...(Args)
			<< ")>" << endl;
		cout << "  - Log::ctor(Vs...(" << sizeof...(Vs) << "))" << endl;
	}

	std::ostream& m_strm;

	template <class T, class ...Vs> LOG_T& o(T&& t, Vs&& ...vs)
	{
		std::lock_guard lg(m_mtx);

		m_strm << "LOG: ";
		base::o(m_strm, std::forward<Vs>(vs)...);
		m_strm << " " << t << endl;
		return *this;
	}
};


template <class T> struct LogTmp;

template <class Strm>
struct LogBase
{
	LogBase(Strm& strm) : m_strm(strm)
	{
		
	}
	

	template <class V>
	LogTmp<Strm>& Write(V&& v)
	{
		m_strm << v;
		return LogTmp<Strm>(std::move(m_lock));
	}


	inline static std::mutex m_mtx;
	std::unique_lock<std::mutex> m_lock;
	Strm& m_strm;
};


template <class T>
struct LogTmp
{
	LogTmp(std::unique_lock<std::mutex>&& lock)
	{
		m_lock.swap(lock);
	}
	std::unique_lock<std::mutex> m_lock;

	template <class V>
	LogTmp Write(V&& v)
	{

	}
};


} //namespace Log

