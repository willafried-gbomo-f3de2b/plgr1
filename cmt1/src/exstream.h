#pragma once

#include <string>
#include <mutex>

#include <iostream>
#include <iomanip>


namespace exstream {

	struct A {
		int n;
	};

	using std::cout, std::endl;

	namespace detail {

		typedef std::mutex mutex_type;
		typedef std::unique_lock<mutex_type> lock_type;

		template <class Strm>
		class tmp
		{
			typedef typename Strm::stream_type ST;
			friend Strm;

			Strm& m_strm;
			lock_type m_lock;

			tmp(Strm& strm, lock_type&& lck) : m_strm(strm)
			{
				
				m_lock.swap(lck);
				//cout << "tmp::ctor(Strm)" << endl;
			}

		public:
			~tmp()
			{
				//cout << "tmp::dtor(Strm)" << endl;
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
			// cout << "ostream::ctor(Strm)" << endl;
		}

		~ostream()
		{
			// cout << "ostream::dtor(Strm)" << endl;
		}

		template <class T>
		Tmp operator<<(T&& t)
		{
			detail::lock_type lck(m_mtx);
			shl(std::forward<T>(t));
			return Tmp(*this, std::move(lck));
		}

		Tmp operator<<(Strm& (*pf)(Strm&))
		{
			detail::lock_type lck(m_mtx);
			shl(pf);
			return Tmp(*this, std::move(lck));
		}

	private:
		typedef Strm stream_type;

		Strm& m_strm;
		std::mutex m_mtx;

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
