#pragma comment(lib,"TestStaticLib.lib")
#include "Header.h"
int main()
{
    std::wstring name = GetNameFile();
    StartThread(name);


}