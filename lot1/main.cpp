#include "sep.h"

#include <windows.h>

#include <iostream>
#include <string>

using std::cout, std::wcout, std::endl, std::hex;

int main(void)
{
    cout << "main." << endl;

    f1();

    LCID lcid = ::GetThreadLocale();
    cout << "GetThreadLocale, LCID: 0x" << hex << lcid << endl;

    char *l1;
    // l1 = setlocale(LC_ALL, "English_United States.utf8");
    l1 = setlocale(LC_ALL, nullptr);
    cout << "setlocale(), -> " << (l1 ? l1 : "?") << endl;

    lcid = ::GetThreadLocale();
    cout << "GetThreadLocale, LCID: 0x" << hex << lcid << endl;

    l1 = setlocale(LC_ALL, "");
    cout << "setlocale(), -> " << (l1 ? l1 : "?") << endl;


    cout << "end." << endl;
}
