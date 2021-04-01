#include "sep.h"

#include <windows.h>

#include <iostream>
#include <string>

using std::cout, std::wcout, std::endl, std::hex;

int main(void)
{
	cout << "main." << endl;

	f1();

	::SetThreadLocale(0x0400);
	
	LCID lcid = ::GetThreadLocale();
	cout << "GetThreadLocale, LCID: 0x" << hex << lcid << endl;

	wchar_t ws[] = L"ABCあいう123";
	wcout << "ws = " << ws << endl;

	char buf[100] = {};
	size_t s = wcstombs(buf, ws, sizeof buf);
	cout << "ws-org-mbs = " << s << ", " << buf << endl;

	f2(ws);

	char *l1;
	// l1 = setlocale(LC_ALL, "English_United States.utf8");
	l1 = setlocale(LC_ALL, nullptr);
	cout << "setlocale(), -> " << (l1 ? l1 : "?") << endl;

	//f1();
	f2(ws);

	lcid = ::GetThreadLocale();
	cout << "GetThreadLocale, LCID: 0x" << hex << lcid << endl;

	l1 = setlocale(LC_ALL, "");
	cout << "setlocale(\"\"), -> " << (l1 ? l1 : "?") << endl;

	buf[0] = 0;
	s = wcstombs(buf, ws, sizeof buf);
	cout << "ws-org-mbs = " << s << ", " << buf << endl;

	//f1();
	f2(ws);

	cout << "end." << endl;
}
