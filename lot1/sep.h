#pragma once

#ifdef SEP_EXPORT
#define SEP_API __declspec(dllexport)
#else
#define SEP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	SEP_API void f1(void);

	SEP_API void f2(const wchar_t *str);

#ifdef __cplusplus
}
#endif