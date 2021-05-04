#pragma once 

#include <mutex>

#include <iostream>


enum LOGLEVEL {
	Fatal, Error, Warn, Info, Debug
};



namespace Log {

using std::cout, std::endl;


template <class CharT, class ...Crgs> struct Log2
{
	Log2()
	{
		cout << "template <" << typeid(CharT).name() << ", class ...Crgs("
			<< sizeof...(Crgs) << ")> struct Log2" << endl;
		cout << "  - Log2::ctor()" << endl;
	}
	inline static std::mutex m_mtx;

	void o(std::ostream& strm)
	{
		strm << "";
	}
};


template <class CharT, class T, class ...Crgs>
struct Log2<CharT, T, Crgs...> : Log2<CharT, Crgs...>
{
	typedef Log2<CharT, Crgs...> base;

	template <class V0, class ...Vs>
	Log2(V0&& v0, Vs&& ...vs) : base(std::forward<Vs>(vs)...), m_def(v0)
	{
		cout << "template <" << typeid(CharT).name() << ", "
			<< typeid(T).name() << ", class ...Crgs(" << sizeof...(Crgs)
			<< ")> struct Log2<" << typeid(CharT).name() << ", "
			<< typeid(T).name() << ", Crgs...(" << sizeof...(Crgs)
			<< ")> : Log2<" << typeid(CharT).name() << ", Crgs...("
			<< sizeof...(Crgs) << ")>" << endl;
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



template <class CharT, class ...Crgs>
struct Log : Log2<CharT, Crgs...>
{
	typedef Log2<CharT, Crgs...> base;
	typedef Log<CharT, Crgs...> LOG_T;

	template <class ...Vs>
	Log(std::ostream& strm, Vs&& ...vs) : Log2(std::forward<Vs>(vs)...),
		m_strm(strm)
	{
		cout << "template <" << typeid(CharT).name() << ", class ...Crgs("
			<< sizeof...(Crgs) << ")> struct Log : Log2<"
			<< typeid(CharT).name() << ", Crgs...(" << sizeof...(Crgs)
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


template <class T> struct C;

template <class T, class Base> struct A : Base
{
	A(std::unique_lock<std::mutex> ul, const char* p) {
		m.swap(ul);
		cout << "A::A()" << endl;
		f(p);
	}
	A(const A&) { cout << "A::A(const A&)" << endl; }
	A(A&& r) {
		m.swap(r.m);
		cout << "A::A(A&&)" << endl;
	}
	~A() { cout << "A::~A()" << endl; }
	A& operator=(const A&) { cout << "A::op=(const A&)" << endl; }
	A& operator=(A&&) { cout << "A::op=(A&&)" << endl; }
	template <class T> A(T&& t) {
		cout << "temp<T> A::A(T&&)" << endl;
	}

	A& f(const char* p) {
		cout << "A::f(), " << p << endl;
		return *this;
	}

	std::unique_lock<std::mutex> m;
};

template <class T> struct C
{
	C() { cout << "C::C()" << endl; }
	C(const C&) { cout << "C::C(const C&)" << endl; }
	C(C&&) { cout << "C::C(C&&)" << endl; }
	~C() { cout << "C::~C()" << endl; }
	C& operator=(const C&) { cout << "C::op=(const C&)" << endl; }
	C& operator=(C&&) { cout << "C::op=(C&&)" << endl; }
};

template <class T> struct B
{
	A<T, B> f(const char* p) {
		std::unique_lock<std::mutex> ul(m_mtx);
		// A<int, B> a(std::move(ul), p);
		// return std::move(a);
		return A<int, B>(std::move(ul), p);
	}
	std::mutex m_mtx;
};


} //namespace Log

