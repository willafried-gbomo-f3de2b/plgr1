//#define COM_EXPORT
#include "sep.h"

#include <iostream>
#include <string>

using std::cout, std::wcout, std::endl;

SEP_API void f1(void)
{
	cout << "dll.f1()" << endl;

	char *l1;
	// l1 = setlocale(LC_ALL, "English_United States.utf8");
	l1 = setlocale(LC_ALL, nullptr);
	cout << "setlocale(), -> " << (l1 ? l1 : "?") << endl;

	cout << "dll.f1().end." << endl;
}
