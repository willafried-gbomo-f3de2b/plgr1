#pragma once

#include <vector>
#include <string>
#include <string_view>

#ifdef WIN32
#include <Windows.h>
#else //#ifdef WIN32
#include <unistd.h>
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

#else //#ifdef WIN32

template <class charT>
inline std::string GetSelfPathTmpl(void)
{
	std::vector<char> buf(1000);
	ssize_t n = readlink("/proc/self/exe", buf.data(), buf.size());
	if (n > 0) {
		return std::string(&buf.front(), n);
	}
	return "";
}

template <class charT>
std::basic_string<charT> GetSelfDirTmpl(void)
{
	typedef std::basic_string<charT> str_t;
	str_t path = GetSelfPathTmpl<charT>();
	auto pos = path.find_last_of('/');
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
	auto pos = path.find_last_of('/');
	if (pos == str_t::npos) {
		return std::move(path);
	}
	return path.substr(pos + 1);
}

#endif //#ifdef WIN32

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
		return "";
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

} //inline namespace v1


inline namespace v1 {

#ifdef WIN32

template <class charT = char> 
const std::basic_string<charT>& GetSepStringBase(void)
{
	static const std::basic_string<charT> sep = "\\";
	return sep;
}

template <> 
inline const std::basic_string<wchar_t>& GetSepStringBase<wchar_t>(void)
{
	static const std::basic_string<wchar_t> sep = L"\\";
	return sep;
}

#else //#ifdef WIN32

template <class charT = char> 
const std::basic_string<charT>& GetSepStringBase(void)
{
	static const std::basic_string<charT> sep = "/";
	return sep;
}

template <> 
inline const std::basic_string<wchar_t>& GetSepStringBase<wchar_t>(void)
{
	static const std::basic_string<wchar_t> sep = L"/";
	return sep;
}

#endif //#ifdef WIN32

#ifndef UNICODE

inline const std::string& GetSepString(void)
{
	return GetSepStringBase<char>();
}

#else //#ifndef UNICODE

inline const std::string& GetSepString(void)
{
	return GetSepStringBase<wchar_t>();
}

#endif //#ifndef UNICODE

} //inline namespace v1

} //namespace path
