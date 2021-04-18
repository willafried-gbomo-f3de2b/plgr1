
#include <matroska/FileKax.h>
#include <sqlite3/sqlite3ext.h>

#include <iostream>
#include <string>


using std::cout, std::endl;

int main(void)
{
    cout << "main()." << endl;
    matroska_init();

    sqlite3_initialize();
}

