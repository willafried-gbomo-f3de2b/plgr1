
#include "deps.h"

#include <iostream>
#include <string>


using std::cout, std::endl;

int main(void)
{
    cout << "main()." << endl;
    matroska_init();

    sqlite3_initialize();

    UpnpLib* upnplib = nullptr;
    UpnpInit2(&upnplib, nullptr, 0, nullptr);

    auto fsd = FLAC__stream_decoder_new();
    
}

