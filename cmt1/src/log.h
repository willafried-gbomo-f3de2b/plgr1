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
	Log(std::ostream& strm, Vs&& ...vs)
		: base(std::forward<Vs>(vs)...),
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
		std::lock_guard lg(base::m_mtx);

		m_strm << "LOG: ";
		base::o(m_strm, std::forward<Vs>(vs)...);
		m_strm << " " << t << endl;
		return *this;
	}
};


template <class T> struct C;

template <class T, class Base> struct A : Base
{
	template <class V>
	A(std::unique_lock<std::mutex> ul, V&& p) {
		m.swap(ul);
		cout << "A::A()" << endl;
		this->operator<<(std::forward<V>(p));
	}
	A(const A&) { cout << "A::A(const A&)" << endl; }
	A(A&& r) {
		m.swap(r.m);
		cout << "A::A(A&&)" << endl;
	}
	~A() { cout << "A::~A()" << endl; }
	A& operator=(const A&) { cout << "A::op=(const A&)" << endl; }
	A& operator=(A&&) { cout << "A::op=(A&&)" << endl; }
	template <class V> A(V&& t) {
		cout << "temp<T> A::A(T&&)" << endl;
	}

	template <class V>
	A& operator<<(V&& p) {
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
	template <class V>
	A<T, B> operator<<(V&& p) {
		std::unique_lock<std::mutex> ul(m_mtx);
		return A<int, B>(std::move(ul), std::forward<V>(p));
	}
	std::mutex m_mtx;
};


template <class T>
class Os : public std::ostream
{
public:
	Os() : std::ostream(std::cout.rdbuf()) {}

	template <class V>
	A<T, Os> operator<<(V&& p) {
		std::unique_lock<std::mutex> ul(m_mtx);
		return A<T, Os>(std::move(ul), std::forward<V>(p));
	}
private:
	std::mutex m_mtx;
};


} //namespace Log

