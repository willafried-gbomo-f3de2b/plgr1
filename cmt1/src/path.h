#pragma once

#include <string>
#include <string_view>

#ifdef WIN32
#include <Windows.h>
#include <Psapi.h>
#else //#ifdef WIN32
#endif //#ifdef WIN32

namespace Path {

inline namespace v1 {

#ifdef WIN32

template <class charT>
std::basic_string<charT> GetSelfPathTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	std::vector<charT> buf(1000);
	DWORD n = ::GetModuleFileName(NULL, buf.data(), (DWORD)buf.size());
	if (n == 0 || n == (DWORD)buf.size()) {
		return "";
	}
	return std::basic_string<charT>(&buf.front(), n);
}


template <class charT>
std::basic_string<charT> GetSelfDirTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	str_t path = GetSelfPathTmpl<charT>();
	auto pos = path.find_last_of('\\');
	if (pos == str_t::npos) {
		return std::move(path);
	}
	return path.substr(0, pos);
}


template <class charT>
std::basic_string<charT> GetSelfNameTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	str_t path =  GetSelfPathTmpl<charT>();
	auto pos = path.find_last_of('\\');
	if (pos == str_t::npos) {
		return std::move(path);
	}
	return path.substr(pos + 1);
}


template <class charT>
std::basic_string<charT> GetSelfBaseNameTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	str_t name =  GetSelfNameTmpl<charT>();
	auto pos = name.find_last_of('.');
	if (pos == str_t::npos) {
		return std::move(name);
	}
	return name.substr(0, pos);
}

template <class charT>
std::basic_string<charT> GetSelfExtTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	str_t name =  GetSelfNameTmpl<charT>();
	auto pos = name.find_last_of('.');
	if (pos == str_t::npos) {
		return std::move(name);
	}
	return name.substr(pos + 1);
}

#ifndef UNICODE 

inline std::string GetSelfPath(void)
{
	return GetSelfPathTmpl<char>();
}

inline std::string GetSelfDir(void)
{
	return GetSelfDirTmpl<char>();
}

inline std::string GetSelfName(void)
{
	return GetSelfNameTmpl<char>();
}

inline std::string GetSelfBaseName(void)
{
	return GetSelfBaseNameTmpl<char>();
}

inline std::string GetSelfExt(void)
{
	return GetSelfExtTmpl<char>();
}

#else //#ifndef UNICODE 

inline std::wstring GetSelfPath(void)
{
	return GetSelfPathTmpl<wchar_t>();
}

inline std::wstring GetSelfDir(void)
{
	return GetSelfDirTmpl<wchar_t>();
}

inline std::wstring GetSelfName(void)
{
	return GetSelfNameTmpl<wchar_t>();
}

inline std::wstring GetSelfBaseName(void)
{
	return GetSelfBaseNameTmpl<wchar_t>();
}

inline std::wstring GetSelfExt(void)
{
	return GetSelfExtTmpl<wchar_t>();
}

#endif //#ifndef UNICODE 

#else //#ifdef WIN32

inline std::string GetExeDir(void)
{

}

#endif //#ifdef WIN32

} //inline namespace v1

} //namespace path
