#include <iostream>
#include <Windows.h>
#include "Entry/Initialize.h"

int main()
{
    //std::cout << "Hello World!\n";
    Entry::Initialize();


    /*HMODULE hDll = LoadLibrary(L"D:\\Library\\Peer\\PeerLib\\x64\\Debug\\PeerLib.dll");
    if (hDll == NULL) {
        std::cerr << "Could not load the DLL" << std::endl;
        std::cerr << GetLastError();

    }*/
}
